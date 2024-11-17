#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TEAMS 5         
#define MAX_PLAYERS 6       
#define CURRENT_YEAR 2024   

typedef struct {
    int day;
    int month;
    int year;
} DateOfBirth;

typedef struct {
    char full_name[26];
    int number;
    char role[20];
    DateOfBirth birth_date;
} Player;

typedef struct {
    char team_name[21];
    Player squad[MAX_PLAYERS];
    int num_players;
} Team;

int register_team(Team clubs[], int total_teams);
int recruit_player(Team clubs[], int total_teams);
void search_or_update_player(Team clubs[], int total_teams);
void list_all_teams(const Team clubs[], int total_teams);
float compute_average_age(const Team club);
int is_team_registered(const Team clubs[], int total_teams, const char team_name[]);
int is_player_registered(const Player squad[], int num_players, const char player_name[]);
int is_kit_number_taken(const Player squad[], int num_players, int kit_number);
void clear_input_buffer();

int main() {
    Team clubs[MAX_TEAMS] = {0}; 
    int total_teams = 0;        
    int option;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Register a Team\n");
        printf("2. Recruit a Player\n");
        printf("3. Search/Update Player\n");
        printf("4. List All Teams\n");
        printf("5. Exit\n");
        printf("Select an option: ");
        scanf("%d", &option);
        clear_input_buffer(); 

        if (option == 1) {
            total_teams = register_team(clubs, total_teams);
        } else if (option == 2) {
            total_teams = recruit_player(clubs, total_teams);
        } else if (option == 3) {
            search_or_update_player(clubs, total_teams);
        } else if (option == 4) {
            list_all_teams(clubs, total_teams);
        } else if (option == 5) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid option. Try again.\n");
        }
    }
    return 0;
}

int register_team(Team clubs[], int total_teams) {
    if (total_teams >= MAX_TEAMS) {
        printf("Cannot register more teams. Limit reached.\n");
        return total_teams;
    }

    printf("Enter team name: ");
    char name[21];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    if (is_team_registered(clubs, total_teams, name)) {
        printf("Team name already exists. Please choose a different name.\n");
        return total_teams;
    }

    strcpy(clubs[total_teams].team_name, name);
    clubs[total_teams].num_players = 0;
    printf("Team registered successfully!\n");
    return total_teams + 1; 
}

int recruit_player(Team clubs[], int total_teams) {
    if (total_teams == 0) {
        printf("No teams registered. Please register a team first.\n");
        return total_teams;
    }

    printf("Select a team to recruit a player to:\n");
    for (int i = 0; i < total_teams; i++) {
        printf("%d. %s\n", i + 1, clubs[i].team_name);
    }

    int team_choice;
    printf("Enter your choice: ");
    scanf("%d", &team_choice);
    clear_input_buffer();

    if (team_choice < 1 || team_choice > total_teams) {
        printf("Invalid team selection. Try again.\n");
        return total_teams;
    }

    int team_index = team_choice - 1;
    if (clubs[team_index].num_players >= MAX_PLAYERS) {
        printf("Player limit reached for this team.\n");
        return total_teams;
    }

    int current_player_count = clubs[team_index].num_players;

    printf("Enter player's full name: ");
    char player_name[26];
    fgets(player_name, sizeof(player_name), stdin);
    player_name[strcspn(player_name, "\n")] = 0;

    if (is_player_registered(clubs[team_index].squad, current_player_count, player_name)) {
        printf("Player with this name already exists. Please try again.\n");
        return total_teams;
    }

    strcpy(clubs[team_index].squad[current_player_count].full_name, player_name);

    printf("Enter kit number: ");
    int kit_number;
    scanf("%d", &kit_number);
    clear_input_buffer();

    if (is_kit_number_taken(clubs[team_index].squad, current_player_count, kit_number)) {
        printf("This kit number is already assigned. Try again.\n");
        return total_teams;
    }

    clubs[team_index].squad[current_player_count].number = kit_number;

    printf("Enter player's position: ");
    fgets(clubs[team_index].squad[current_player_count].role, sizeof(clubs[team_index].squad[current_player_count].role), stdin);
    clubs[team_index].squad[current_player_count].role[strcspn(clubs[team_index].squad[current_player_count].role, "\n")] = 0;

    printf("Enter date of birth (dd mm yyyy): ");
    scanf("%d %d %d", &clubs[team_index].squad[current_player_count].birth_date.day,
          &clubs[team_index].squad[current_player_count].birth_date.month,
          &clubs[team_index].squad[current_player_count].birth_date.year);
    clear_input_buffer();

    clubs[team_index].num_players++;
    printf("Player successfully recruited!\n");
    return total_teams;
}

void list_all_teams(const Team clubs[], int total_teams) {
    if (total_teams == 0) {
        printf("No teams registered.\n");
        return;
    }

    for (int i = 0; i < total_teams; i++) {
        printf("\nTeam: %s\n", clubs[i].team_name);
        printf("Players:\n");
        if (clubs[i].num_players == 0) {
            printf("  No players in this team yet.\n");
        } else {
            for (int j = 0; j < clubs[i].num_players; j++) {
                printf("  Name: %s, Kit: %d, Role: %s, DOB: %02d/%02d/%04d\n",
                       clubs[i].squad[j].full_name,
                       clubs[i].squad[j].number,
                       clubs[i].squad[j].role,
                       clubs[i].squad[j].birth_date.day,
                       clubs[i].squad[j].birth_date.month,
                       clubs[i].squad[j].birth_date.year);
            }
        }
    }
}

void search_or_update_player(Team clubs[], int total_teams) {
    if (total_teams == 0) {
        printf("No teams registered yet.\n");
        return;
    }

    printf("Search by:\n");
    printf("1. Player Name\n");
    printf("2. Kit Number\n");
    printf("Select an option: ");
    int choice;
    scanf("%d", &choice);
    clear_input_buffer();

    int found = 0; 

    if (choice == 1) {
        char search_name[26];
        printf("Enter player's name: ");
        fgets(search_name, sizeof(search_name), stdin);
        search_name[strcspn(search_name, "\n")] = '\0'; 

        for (int i = 0; i < total_teams; i++) {
            for (int j = 0; j < clubs[i].num_players; j++) {
                if (strcasecmp(search_name, clubs[i].squad[j].full_name) == 0) {
                    found = 1;
                    printf("\nPlayer found in team '%s':\n", clubs[i].team_name);
                    printf("Name: %s, Kit: %d, Position: %s, DOB: %02d/%02d/%04d\n",
                           clubs[i].squad[j].full_name,
                           clubs[i].squad[j].number,
                           clubs[i].squad[j].role,
                           clubs[i].squad[j].birth_date.day,
                           clubs[i].squad[j].birth_date.month,
                           clubs[i].squad[j].birth_date.year);

                    printf("\nUpdate player details:\n");

                    printf("Enter new name (or press Enter to keep current): ");
                    char new_name[26];
                    fgets(new_name, sizeof(new_name), stdin);
                    if (strcspn(new_name, "\n") > 0) {
                        new_name[strcspn(new_name, "\n")] = '\0';
                        strcpy(clubs[i].squad[j].full_name, new_name);
                    } else {
                        printf("Name retained as: %s\n", clubs[i].squad[j].full_name);
                    }

                    printf("Enter new kit number (or press Enter to keep current): ");
                    char new_kit_number_str[10];
                    fgets(new_kit_number_str, sizeof(new_kit_number_str), stdin);
                    if (strcspn(new_kit_number_str, "\n") > 0) {
                        int new_kit_number = atoi(new_kit_number_str);
                        if (new_kit_number > 0) {
                            clubs[i].squad[j].number = new_kit_number;
                        } else {
                            printf("Invalid kit number. Retaining current number: %d\n", clubs[i].squad[j].number);
                        }
                    } else {
                        printf("Kit number retained as: %d\n", clubs[i].squad[j].number);
                    }
                }
            }
        }
    }
}

int is_team_registered(const Team clubs[], int total_teams, const char team_name[]) {
    for (int i = 0; i < total_teams; i++) {
        if (strcasecmp(clubs[i].team_name, team_name) == 0) {
            return 1; 
        }
    }
    return 0;
}

int is_player_registered(const Player squad[], int num_players, const char player_name[]) {
    for (int i = 0; i < num_players; i++) {
        if (strcasecmp(squad[i].full_name, player_name) == 0) {
            return 1;  
        }
    }
    return 0;
}

int is_kit_number_taken(const Player squad[], int num_players, int kit_number) {
    for (int i = 0; i < num_players; i++) {
        if (squad[i].number == kit_number) {
            return 1;  
        }
    }
    return 0;
}

void clear_input_buffer() {
    while (getchar() != '\n');  
}
