#include <concord/discord.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define LIBH
#ifdef LIBH

int StartsWith(const char *a, const char *b)
{

    if (strncmp(a, b, strlen(b)) == 0)
        return 1;
    return 0;
}
const char *kills[] =
    {
        "has drowned in money!", "got sniped!", "got poisoned!", "fell in the shower!",
        "got cancer!", "got ran over by a car!", "fell out of a plane!", "lost their phone!",
        "was eaten by a shark!", "remembered an embarrassing moment from 2 years ago!", "fell down the stairs!",
        "spontaneously died!", "didnt do their math homework!", "got electrocuted!", "got an F on their test!",
        "got stabbed!", "stubbed their toe!", "power went out while updating BIOS!", "got hit by an avalanche!",
        "was caught lackin!", "got one tapped!", "got checkmated!", "got a virus!", "got forced to watch twilight!",
        "got bit by a zombie!", "got bit by vampires!", "was the last one to finish a lap during pe!(fatty)", "deranked in val!",
        "broke their hand!", "Segmentation fault (core dumped)"};

int checkForHelp(struct discord *client, const struct discord_message *event)
{
    if (StartsWith(event->content, "!pls help") == 1)
    {
        char *helpMessage = "use !pls kill @<person> to use this bot";
        struct discord_create_message help_params = {
            .content = helpMessage,
        };
        discord_create_message(client, event->channel_id, &help_params, NULL);
        return 1;
    }
    return 0;
}

#endif