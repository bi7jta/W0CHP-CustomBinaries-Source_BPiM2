/*
*   Copyright (C) 2023 by Chip Cuccio, W0CHP
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <mosquitto.h>
#include <cjson/cJSON.h>
#include <ini.h>
#define MAX_MESSAGES 300

struct topic_data
{
	char *topic;
	char *output_file;
	cJSON * messages;
};

static void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
    struct topic_data *data = (struct topic_data *) obj;

    // write raw JSON to file
    FILE *fp = fopen(data->output_file, "a");  // use append mode to avoid overwriting previous content
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening file %s: %s\n", data->output_file, strerror(errno));
        return;
    }

    fprintf(fp, "%.*s\n", (int)msg->payloadlen, (char *)msg->payload);
    fclose(fp);

    // remove oldest message if we've reached the maximum
    int num_messages = cJSON_GetArraySize(data->messages);
    if (num_messages >= MAX_MESSAGES)
    {
        cJSON_DeleteItemFromArray(data->messages, 0);
    }

    // add message to cJSON array
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "topic", msg->topic);
    cJSON_AddNumberToObject(json, "qos", msg->qos);
    cJSON_AddStringToObject(json, "payload", (char *)msg->payload);
    cJSON_AddItemToArray(data->messages, json);
}

static int read_config(void *user, const char *section, const char *name, const char *value)
{
	struct topic_data *data = (struct topic_data *) user;

	if (strcmp(name, "topic") == 0)
	{
		data->topic = strdup(value);
	}
	else if (strcmp(name, "output_file") == 0)
	{
		data->output_file = strdup(value);
	}

	return 1;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s config_file\n", argv[0]);
		return EXIT_FAILURE;
	}

	// read config file
	struct topic_data topics[10];
	memset(topics, 0, sizeof(topics));
	int num_topics = 0;

	if (ini_parse(argv[1], read_config, &topics) < 0)
	{
		fprintf(stderr, "Error parsing config file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 10; i++)
	{
		if (topics[i].topic == NULL)
		{
			break;
		}

		// initialize cJSON array
		topics[i].messages = cJSON_CreateArray();
		if (topics[i].messages == NULL)
		{
			fprintf(stderr, "Error creating JSON array\n");
			return EXIT_FAILURE;
		}

		// connect to MQTT broker
		struct mosquitto *mosq = mosquitto_new(NULL, true, &topics[i]);
		if (mosq == NULL)
		{
			fprintf(stderr, "Error creating mosquitto client\n");
			return EXIT_FAILURE;
		}

		if (mosquitto_connect(mosq, "localhost", 1883, 60) != MOSQ_ERR_SUCCESS)
		{
			fprintf(stderr, "Error connecting to MQTT broker: %s\n", mosquitto_strerror(errno));
			return EXIT_FAILURE;
		}

		if (mosquitto_subscribe(mosq, NULL, topics[i].topic, 0) != MOSQ_ERR_SUCCESS)
		{
			fprintf(stderr, "Error subscribing to topic %s: %s\n", topics[i].topic, mosquitto_strerror(errno));
			return EXIT_FAILURE;
		}

		mosquitto_message_callback_set(mosq, on_message);

		// enter event loop
		if (mosquitto_loop_forever(mosq, -1, 1) != MOSQ_ERR_SUCCESS)
		{
			fprintf(stderr, "Error in mosquitto event loop\n");
			return EXIT_FAILURE;
		}

		mosquitto_destroy(mosq);
		mosquitto_lib_cleanup();
	}

	return EXIT_SUCCESS;

}
