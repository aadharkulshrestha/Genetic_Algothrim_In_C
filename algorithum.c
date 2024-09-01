#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define POPULATION_SIZE 50
#define SELECTION_SIZE_MALE 5
#define SELECTION_SIZE_FEMALE 5

typedef struct {
    char name[50];
    char gender[10];
    char hair_color[20];
    char eye_color[20];
    char ear_lobe[20];
    char height[20];
} Individual;

void generate_initial_population(Individual population[]);
int fitness(Individual individual, Individual target);
void selection(Individual population[], Individual target_male, Individual target_female, Individual males[], Individual females[]);

void generate_initial_population(Individual population[]) {
    const char* names[] = {"Person1", "Person2", "Person3","Person4", "Person5", "Person6","Person7", "Person8", "Person9","Person10", "Person11", "Person12","Person13", "Person14", "Person15","Person16", "Person17", "Person18","Person19", "Person20", "Person21","Person22", "Person23", "Person24","Person25", "Person26", "Person27","Person28", "Person29", "Person30","Person31", "Person32", "Person33","Person34", "Person35", "Person36","Person37", "Person38","Person39", "Person40", "Person41","Person42", "Person43", "Person44","Person45", "Person46", "Person47","Person48", "Person49", "Person50", /* ... up to 50 */};
    const char* genders[] = {"Male", "Female"};
    const char* hair_colors[] = {"Blonde", "Black", "Brown", "Red"};
    const char* eye_colors[] = {"Blue", "Brown", "Green", "Hazel"};
    const char* ear_lobes[] = {"Attached", "Detached"};
    const char* heights[] = {"Tall", "Short"};

    for (int i = 0; i < POPULATION_SIZE; i++) {
        strcpy(population[i].name, names[i % (sizeof(names) / sizeof(names[0]))]);
        strcpy(population[i].gender, genders[rand() % 2]);
        strcpy(population[i].hair_color, hair_colors[rand() % 4]);
        strcpy(population[i].eye_color, eye_colors[rand() % 4]);
        strcpy(population[i].ear_lobe, ear_lobes[rand() % 2]);
        strcpy(population[i].height, heights[rand() % 2]);
    }
}


int fitness(Individual individual, Individual target) {
    int score = 0;
    if (target.gender[0] != '\0' && strcmp(individual.gender, target.gender) == 0) score++;
    if (target.hair_color[0] != '\0' && strcmp(individual.hair_color, target.hair_color) == 0) score++;
    if (target.eye_color[0] != '\0' && strcmp(individual.eye_color, target.eye_color) == 0) score++;
    if (target.ear_lobe[0] != '\0' && strcmp(individual.ear_lobe, target.ear_lobe) == 0) score++;
    if (target.height[0] != '\0' && strcmp(individual.height, target.height) == 0) score++;
    return score;
}


void selection(Individual population[], Individual target_male, Individual target_female, Individual males[], Individual females[]) {
    int male_count = 0, female_count = 0;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        if (strcmp(population[i].gender, "Male") == 0) {
            if (male_count < SELECTION_SIZE_MALE) {
                males[male_count++] = population[i];
            }
        } else if (strcmp(population[i].gender, "Female") == 0) {
            if (female_count < SELECTION_SIZE_FEMALE) {
                females[female_count++] = population[i];
            }
        }
    }
}


int main() {
    srand(time(NULL));

    Individual population[POPULATION_SIZE];
    Individual selected_males[SELECTION_SIZE_MALE];
    Individual selected_females[SELECTION_SIZE_FEMALE];

    // Target individuals for males and females
    Individual target_male = {"", "Male", "Blonde", "Blue", "Attached", "Tall"};
    Individual target_female = {"", "Female", "Blonde", "Blue", "Detached", "Tall"};

    // Generate initial population
    generate_initial_population(population);

    // Selection process
    selection(population, target_male, target_female, selected_males, selected_females);

    // Print the selected individuals
    printf("Selected Males:\n");
    for (int i = 0; i < SELECTION_SIZE_MALE; i++) {
        printf("%s - %s - %s - %s - %s - %s\n", selected_males[i].name, selected_males[i].gender, selected_males[i].hair_color, selected_males[i].eye_color, selected_males[i].ear_lobe, selected_males[i].height);
    }

    printf("Selected Females:\n");
    for (int i = 0; i < SELECTION_SIZE_FEMALE; i++) {
        printf("%s - %s - %s - %s - %s - %s\n", selected_females[i].name, selected_females[i].gender, selected_females[i].hair_color, selected_females[i].eye_color, selected_females[i].ear_lobe, selected_females[i].height);
    }

    return 0;
}
