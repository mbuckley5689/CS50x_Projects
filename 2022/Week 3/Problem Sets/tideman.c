#include <cs50.h>
#include <stdio.h>
#include <string.h>

// The purpose of this code is to complete the "tideman" assignment from the week 3 problem set for
// the 2022 session of the CS50: Introduction to Computer Science course. The prompt for the assignment can be accessed via the URL below:

// https://cs50.harvard.edu/x/2022/psets/3/tideman/

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // sweep through each of the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if the indexed candidate is the same as the input name,
        // update the ranks array with the rank of the input name & return true
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // if none of the candidates match the input name, then return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // sweep through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // sweep through each candidate again
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // sweeps through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // sweeps through the candidates
        for (int j = i; j < candidate_count; j++)
        {
            // if the ith candidate has more votes than the jth candidate,
            // add a pair with the ith candidate as the winner.
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // if the jth candidate has more votes than the ith candidate,
            // add a pair with the jth candidate as the winner.
            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        int pair_now = preferences[pairs[i].winner][pairs[i].loser];
        int pair_next = preferences[pairs[i + 1].winner][pairs[i + 1].loser];
        if (pair_now < pair_next)
        {
            pair placeholder_small = pairs[i];
            pair placeholder_large = pairs[i + 1];
            pairs[i] = placeholder_large;
            pairs[i + 1] = placeholder_small;
            i = -1;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // sweep through pairs
    for (int i = 0; i < pair_count; i++)
    {
        int queue_max = MAX * MAX; // maximum length of the queue
        int queue[queue_max]; // initialize a queue with length queue_max
        int dequeue[queue_max]; // initializes an array with all indices "dropped" from the queue
        int dequeue_end = 0; // initiailize the ending index of dequeue array
        int queue_start = 0; // initialize the starting index of the active queue
        int queue_end = 0; // initialize the ending index of the active queue
        int pair_now = pairs[i].winner; // winner of currently indexed "pair"
        int pair_now_loser = pairs[i].loser; // loser of currently indexed "pair"
        int queue_length = 1; // length of the active queue.
        queue[0] = pairs[i].winner; // sets the 1st element of the queue to be the index of the winner of the indexed pair
        locked[pair_now][pair_now_loser] = true; // initially set a locked edge for the currently indexed winner

        // sweep through the queue, checking for cycles
        for (int m = queue_start; m < queue_end + 1; m++)
        {
            pair_now = queue[queue_end];
            // sweep through all candidate matchups with the candidate at the end of the queue
            for (int j = 0; j < candidate_count; j++)
            {
                int pair_check = j;
                // add all locked pairs to the queue
                if (locked[pair_check][pair_now] == true)
                {
                    queue_end++;
                    queue[queue_end] = pair_check;
                }
            }

            dequeue[dequeue_end] = queue[queue_start]; // add the about-to-be-dropped queue element to the dequeue array
            queue_start++; // "drop" the starting element from the queue
            dequeue_end++; // update the final index of the queue
            queue_length = queue_end - queue_start; // recalculate the length of the active queue
            bool cycle_check = false; // initializes flag for detecting cycles

            // checks to see if any nodes in the queue have already been dequeued.
            // if they have, then created a locked edge will create a cycle
            for (int k = queue_start; k < queue_end + 1; k++) // cycles through the queue
            {
                for (int n = 0; n < dequeue_end; n++) // cycles through the dequeue
                {
                    if (queue[k] == dequeue[n])
                    {
                        cycle_check = true; // set cycle detection flag to true
                    }
                }
            }

            // if there's a cycle, exit the locked pair loop
            // for the currently indexed "base node", without
            // adding a locked edge
            if (cycle_check == true)
            {
                m = queue_end + 1;
                locked[pairs[i].winner][pairs[i].loser] = false;
            }

            // if there is not a cycle, and there is still a queue,
            // continue cycling through the queue, looking for a cycle
            if (cycle_check == false && queue_length >= 0)
            {
                m = queue_start - 1;
            }

            // if neither of the two above "if-statements" are true,
            // then finalize the locked edge initialized in the beginning
            // of this function.
        }
    }
    return;
}

// Print the winner of the election by finding all "sources"
// of the election graph. this is done by sweeping through the
// "locked[][]" array. Any column of this array that has all
// "false" values, is a source.
void print_winner(void)
{
    string source[pair_count]; // initialize an array of possible election "sources"
    int source_index = 0; // initializes current index of the "source" array

    // sweep through losers
    for (int i = 0; i < candidate_count; i++)
    {
        bool source_check = true; // initializes flag indicating that the indexed pair is a source
        int source_counter = 0; // init. counter that counts # of "true" values in an indexed column of locked[][]
        // sweep through winners
        for (int j = 0; j < candidate_count; j++)
        {
            // record if a candidate is not a source
            if (locked[j][i] == true)
            {
                source_counter++;
            }
        }
        if (source_counter == 0) // add indexed column-candidate as a source & increase source index if true
        {
            source[source_index] = candidates[i];
            source_index++;
        }
    }

    for (int i = 0; i < source_index; i++) // print all winners (entries in the source array)
    {
        printf("%s\n", source[i]);
    }
    return;
}
