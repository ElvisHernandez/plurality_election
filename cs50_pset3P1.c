#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
bool compare_strings(string one, string two);
int merge_sort(int nums[], int nums_length);
void merge_halfs(int nums[],int la[], int la_len, int ra[], int ra_len);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++) {
        if (compare_strings(candidates[i].name,name)) {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int votes[candidate_count];

    for (int i = 0; i < candidate_count; i++) {
        votes[i] = candidates[i].votes;
    }
    merge_sort(votes,candidate_count);
    int max_votes = votes[candidate_count-1];

    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == max_votes) {
            printf("%s\n", candidates[i].name);
        }
    }

    // TODO
    return;
}

bool compare_strings(string one, string two) {
    for (int i = 0; one[i] != '\0'; i++) {
        if (one[i] != two[i]) return false;
    }
    for (int i = 0; two[i] != '\0'; i++) {
        if (two[i] != one[i]) return false;
    }
    return true;
}

int merge_sort(int nums[], int nums_length) {
    if (nums_length == 1)
        return 0;
    int mid = nums_length/2;
    int la[mid];
    int ra[nums_length-mid];
    for (int i = 0; i < mid; i++) {
        la[i] = nums[i];
    }
    for (int i = 0; i < nums_length-mid; i++) {
        ra[i] = nums[mid+i];
    }
    merge_sort(la, mid);
    merge_sort(ra,nums_length-mid);
    merge_halfs(nums,la,mid,ra, nums_length-mid);
    return 0;
}

void merge_halfs(int nums[],int la[], int la_len, int ra[], int ra_len) {
    int merged_array[la_len + ra_len];
    int la_i = 0;
    int ra_i = 0; // these are the left, right, and merged arrays respectively
    int ma_i = 0;

    while (la_i < la_len && ra_i < ra_len) {
        if (la[la_i] < ra[ra_i]) {
            merged_array[ma_i] = la[la_i];
            la_i++;
        } else {
            merged_array[ma_i] = ra[ra_i];
            ra_i++;
        }
        ma_i++;
    }
    while (la_i < la_len) {
        merged_array[ma_i] = la[la_i];
        la_i++;
        ma_i++;
    }
    while (ra_i < ra_len) {
        merged_array[ma_i] = ra[ra_i];
        ra_i++;
        ma_i++;
    }
    for (int i = 0; i < (la_len + ra_len); i++) {
        nums[i] = merged_array[i];
        //printf("Merged array element %i: %i\n", i+1,merged_array[i]);
    }
}
