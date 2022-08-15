#include "lib.h"
/** @author mess#6930 */
/** @brief kill bot based on previous javascript implementation */

void print_usage(void)
{
    printf("\n\nTYPE ANY KEY TO START CORN BOT\n");
}

void on_ready(struct discord *client, const struct discord_ready *event)
{
    log_info("Corn-Bot succesfully connected to Discord as %s#%s!",
             event->user->username, event->user->discriminator);

    struct discord_activity activities[] = {
        {
            .name = "Corn Bot, this time in C!",
            .type = DISCORD_ACTIVITY_LISTENING,
            .details = "Fixing some bugs",
        },
    };

    struct discord_presence_update status = {
        .activities =
            &(struct discord_activities){
                .size = sizeof(activities) / sizeof *activities,
                .array = activities,
            },
        .status = "idle",
        .afk = false,
        .since = discord_timestamp(client),
    };
    discord_update_presence(client, &status);
}

void on_message_create(struct discord *client, const struct discord_message *event)
{
    if (event->author->bot)
        return;
    if (checkForHelp(client, event) == 1)
        return;

    if (StartsWith(event->content, "!pls kill") == 0)
        return;
    const char *randKill = kills[rand() % (sizeof kills / sizeof kills[0])];
    if (StartsWith(event->content, "!pls kill me") == 1)
    {
        char message[1024];
        sprintf(message, "@%s#%s %s", event->author->username, event->author->discriminator, randKill);
        struct discord_create_message params = {
            .content = message,
        };
        discord_create_message(client, event->channel_id, &params, NULL);
    }
    else
    {
        char message[1024];
        sprintf(message, "@%s#%s %s", event->mentions->array[0].username, event->mentions->array[0].discriminator, randKill);
        struct discord_create_message params = {
            .content = &message,
        };

        discord_create_message(client, event->channel_id, &params, NULL);
    }
}

int main(int argc, char *argv[])
{

    srand((unsigned)clock());
    const char *config_file;
    config_file = "./config.json";

    ccord_global_init();
    struct discord *client = discord_config_init(config_file);
    assert(NULL != client && "Couldn't initialize client");

    discord_set_on_ready(client, &on_ready);
    discord_set_on_message_create(client, &on_message_create);

    print_usage();
    fgetc(stdin); // wait for input

    discord_run(client);

    discord_cleanup(client);
    ccord_global_cleanup();
}
