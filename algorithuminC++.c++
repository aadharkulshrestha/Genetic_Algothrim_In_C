#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define POPULATION_SIZE 50
#define SELECTION_SIZE 10
#define MUTATION_RATE 0.1
#define GENERATIONS 10

using namespace std;


class Individual {
public:
    string name;
    string gender;
    string hair_color;
    string eye_color;
    string ear_lobe;
    string height;

    Individual() {}

    Individual(string name, string gender, string hair_color, string eye_color, string ear_lobe, string height)
        : name(name), gender(gender), hair_color(hair_color), eye_color(eye_color), ear_lobe(ear_lobe), height(height) {}

    Individual(const Individual& other)
        : name(other.name), gender(other.gender), hair_color(other.hair_color), eye_color(other.eye_color), ear_lobe(other.ear_lobe), height(other.height) {}

    Individual& operator=(const Individual& other) {
        if (this != &other) {
            name = other.name;
            gender = other.gender;
            hair_color = other.hair_color;
            eye_color = other.eye_color;
            ear_lobe = other.ear_lobe;
            height = other.height;
        }
        return *this;
    }
};


vector<Individual> generate_initial_population();
int fitness(const Individual &individual, const Individual &target);
vector<Individual> selection(const vector<Individual> &population, const Individual &target);
Individual crossover(const Individual &parent1, const Individual &parent2);
void mutate(Individual &individual);


vector<Individual> generate_initial_population() {
    vector<string> names = {"Person1", "Person2", "Person3","Person4", "Person5", "Person6","Person7", "Person8", "Person9","Person10", "Person11", "Person12","Person13", "Person14", "Person15","Person16", "Person17", "Person18","Person19", "Person20", "Person21","Person22", "Person23", "Person24","Person25", "Person26", "Person27","Person28", "Person29", "Person30","Person31", "Person32", "Person33","Person34", "Person35", "Person36","Person37", "Person38","Person39", "Person40", "Person41","Person42", "Person43", "Person44","Person45", "Person46", "Person47","Person48", "Person49", "Person50", /* ... up to 50 */};
    vector<string> genders = {"Male", "Female"};
    vector<string> hair_colors = {"Black"};
    vector<string> eye_colors = { "Brown", };
    vector<string> ear_lobes = { "Detached"};
    vector<string> heights = {"Tall", "Short"};

    vector<Individual> population;
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        string name = names[i % names.size()];
        string gender = genders[rand() % genders.size()];
        string hair_color = hair_colors[rand() % hair_colors.size()];
        string eye_color = eye_colors[rand() % eye_colors.size()];
        string ear_lobe = ear_lobes[rand() % ear_lobes.size()];
        string height = heights[rand() % heights.size()];
        population.emplace_back(name, gender, hair_color, eye_color, ear_lobe, height);
    }

    return population;
}


int fitness(const Individual &individual, const Individual &target) {
    int score = 0;
    if (!target.gender.empty() && individual.gender == target.gender) score++;
    if (!target.hair_color.empty() && individual.hair_color == target.hair_color) score++;
    if (!target.eye_color.empty() && individual.eye_color == target.eye_color) score++;
    if (!target.ear_lobe.empty() && individual.ear_lobe == target.ear_lobe) score++;
    if (!target.height.empty() && individual.height == target.height) score++;
    return score;
}


vector<Individual> selection(const vector<Individual> &population, const Individual &target) {
    vector<pair<int, Individual>> male_population;
    vector<pair<int, Individual>> female_population;

    // Calculate fitness and separate by gender
    for (const auto &individual : population) {
        int fit_score = fitness(individual, target);
        if (individual.gender == "Male") {
            male_population.push_back({fit_score, individual});
        } else if (individual.gender == "Female") {
            female_population.push_back({fit_score, individual});
        }
    }

    // Sort males and females by fitness score (descending order)
    sort(male_population.begin(), male_population.end(), [](const pair<int, Individual> &a, const pair<int, Individual> &b) {
        return a.first > b.first;
    });

    sort(female_population.begin(), female_population.end(), [](const pair<int, Individual> &a, const pair<int, Individual> &b) {
        return a.first > b.first;
    });

    // Select top 5 males and top 5 females
    vector<Individual> selected_individuals;
    for (int i = 0; i < min(SELECTION_SIZE / 2, static_cast<int>(male_population.size())); ++i) {
        selected_individuals.push_back(male_population[i].second);
    }

    for (int i = 0; i < min(SELECTION_SIZE / 2, static_cast<int>(female_population.size())); ++i) {
        selected_individuals.push_back(female_population[i].second);
    }

    return selected_individuals;
}



Individual crossover(const Individual &parent1, const Individual &parent2) {
    Individual child;
    child.gender = (rand() % 2 == 0) ? parent1.gender : parent2.gender;
    child.hair_color = (rand() % 2 == 0) ? parent1.hair_color : parent2.hair_color;
    child.eye_color = (rand() % 2 == 0) ? parent1.eye_color : parent2.eye_color;
    child.ear_lobe = (rand() % 2 == 0) ? parent1.ear_lobe : parent2.ear_lobe;
    child.height = (rand() % 2 == 0) ? parent1.height : parent2.height;
    return child;
}

void mutate(Individual &individual) {
    vector<string> hair_colors = { "Black", };
    vector<string> eye_colors = { "Brown"};
    vector<string> ear_lobes = { "Detached"};
    vector<string> heights = {"Tall", "Short"};

    if (rand() / double(RAND_MAX) < MUTATION_RATE) {
        individual.hair_color = hair_colors[rand() % hair_colors.size()];
    }
    if (rand() / double(RAND_MAX) < MUTATION_RATE) {
        individual.eye_color = eye_colors[rand() % eye_colors.size()];
    }
    if (rand() / double(RAND_MAX) < MUTATION_RATE) {
        individual.ear_lobe = ear_lobes[rand() % ear_lobes.size()];
    }
    if (rand() / double(RAND_MAX) < MUTATION_RATE) {
        individual.height = heights[rand() % heights.size()];
    }
}
int main() {
    srand(time(nullptr));

    vector<Individual> population = generate_initial_population();

    Individual target("", "Female", "Blonde", "Blue", "Detached", "Tall");

    for (int generation = 0; generation < GENERATIONS; ++generation) {
        vector<Individual> selected_individuals = selection(population, target);
        vector<Individual> next_generation;

        while (next_generation.size() < POPULATION_SIZE) {
            int parent1_index = rand() % SELECTION_SIZE;
            int parent2_index = rand() % SELECTION_SIZE;

            Individual child = crossover(selected_individuals[parent1_index], selected_individuals[parent2_index]);
            mutate(child);
            next_generation.push_back(child);
        }

        population = next_generation;

        cout << "Generation " << generation + 1 << " completed." << endl;
    }

    vector<Individual> final_selection = selection(population, target);

    cout << "\nFinal selected individuals:\n";
    for (const auto &ind : final_selection) {
        cout << ind.name << " - " << ind.gender << " - " << ind.hair_color << " - " << ind.eye_color << " - " << ind.ear_lobe << " - " << ind.height << endl;
    }

    return 0;
}
