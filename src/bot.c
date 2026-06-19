#include <stdio.h>
#include <string.h>
#include <concord/discord.h>
#include <cjson/cJSON.h>

int config (char TOKEN[73]) {
    FILE *fp = fopen("config.json", "r");
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return 1;
    }

    char buffer[1024];
    int len = fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);

    cJSON *jsonp = cJSON_Parse(buffer);
    if (jsonp == NULL) {
        printf("unexplained because cayla is lazy");
        cJSON_Delete(jsonp);
        return 1;
        }

    cJSON *token = cJSON_GetObjectItemCaseSensitive(jsonp, "token");
    if (cJSON_IsString(token) && (token->valuestring != NULL)) {
        strncpy(TOKEN, token->valuestring, 73);
    }

    cJSON_Delete(jsonp);
};




int guild (char GUILD_ID[20]) {
    GUILD_ID = "1281122097778921515";
    return 0;
}

void on_ready(struct discord *client, const struct discord_ready *event) {
    struct discord_create_guild_application_command params = {
        .name = "ping",
        .description = "Ping command!"
    };
    char GUILD_ID[20];
    discord_create_guild_application_command(client, event->application->id,
                                             guild(GUILD_ID), &params, NULL);
}

void on_interaction(struct discord *client, const struct discord_interaction *event) {
    if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND)
        return; /* return if interaction isn't a slash command */

    if (strcmp(event->data->name, "ping") == 0) {
          struct discord_interaction_response params = {
                .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
                .data = &(struct discord_interaction_callback_data){
                      .content = "pong"
                }
          };
          discord_create_interaction_response(client, event->id,
                                              event->token, &params, NULL);
    }
}

int main(void) {
    char TOKEN[73];
    config(TOKEN);
    struct discord *client = discord_init(TOKEN);
    discord_set_on_ready(client, &on_ready);
    discord_set_on_interaction_create(client, &on_interaction);
    discord_run(client);
    printf("We are ready now \n");
}
