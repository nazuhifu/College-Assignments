#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

int playerHealth = 100;

void pressAny()
{
    std::cout << "\nPress any key to continue... ";
    getchar();              // Wait for a key press
    printf("\033[H\033[J"); // Clear the console screen
}

// Struct untuk menyimpan item
struct Item
{
    std::string name;
    int value;
    int quantity;
};

// Struct untuk menyimpan data musuh
struct Enemy
{
    std::string name;
    int health;
    int power;
};

// Struct for a tree node with a parent pointer
struct Node
{
    std::string location;
    Node *parent; // Add a parent pointer
    std::vector<Node *> children;

    Node(const std::string &loc, Node *par = nullptr) : location(loc), parent(par) {}
};

struct JobNode
{
    std::string jobName;
    JobNode *left;
    JobNode *right;

    JobNode(const std::string &name) : jobName(name), left(nullptr), right(nullptr) {}
};

struct Player
{
    int level = 2;
    int experience = 0;
    int maxExperience = 100; // XP required to level up
    JobNode *jobNode = nullptr;
    bool hasMeleeJob = false;
    bool hasRangeJob = false;
    int meleeJobLevel = 2; // Level required
    int rangeJobLevel = 2;
    int advancedJobLevel = 3;
};

void job()
{
    std::cout << R"(
               Player
                 /\
                /  \
           Melee   Range
          /\           /\
    Knight Paladin  Mage Archer
    )" << std::endl;
}

Player player;

JobNode *createJobTree()
{
    JobNode *player = new JobNode("Player");

    JobNode *melee = new JobNode("Melee");
    JobNode *range = new JobNode("Range");

    JobNode *darkKnight = new JobNode("Dark Knight");
    JobNode *paladin = new JobNode("Paladin");
    JobNode *archer = new JobNode("Archer");
    JobNode *mage = new JobNode("Mage");

    player->left = melee;
    player->right = range;

    melee->left = darkKnight;
    melee->right = paladin;

    range->left = archer;
    range->right = mage;

    return player;
}

JobNode *jobTree = createJobTree();

void selectJob(JobNode *jobNode)
{
    player.jobNode = jobNode;
    std::cout << "You have selected the " << player.jobNode->jobName << " class job\n";
}

void chooseMeleeOrRangeJob()
{
    job();

    std::cout << "You have reached level " << player.meleeJobLevel << std::endl;
    std::cout << "Choose you job category: \n";
    std::cout << "1. Melee\n";
    std::cout << "2. Range\n";
    std::cout << "Enter you choice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        player.hasMeleeJob = true;
        selectJob(jobTree->left);
    }
    else if (choice == 2)
    {
        player.hasRangeJob = true;
        selectJob(jobTree->right);
    }
    else
    {
        std::cout << "Invalid choice\n";
    }
}

void chooseAdvancedJob(JobNode *parentNode)
{
    std::cout << "You have reached level " << player.advancedJobLevel << ".\nChoose your advanced job:\n";
    std::cout << "1. " << parentNode->left->jobName << "\n";
    std::cout << "2. " << parentNode->right->jobName << "\n";
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        selectJob(parentNode->left);
    }
    else if (choice == 2)
    {
        selectJob(parentNode->right);
    }
    else
    {
        std::cout << "Invalid choice. You can choose your advanced job later.\n";
    }
}

void chooseJob()
{
    if (player.level < player.meleeJobLevel)
    {
        std::cout << "\nYou need to reach level " << player.meleeJobLevel << " to choose a job category.\n";

        pressAny();
        return;
    }

    if (!player.hasMeleeJob && !player.hasRangeJob)
    {
        chooseMeleeOrRangeJob();
    }
    else if (player.level >= player.advancedJobLevel && player.jobNode != nullptr)
    {
        chooseAdvancedJob(player.jobNode->left->left ? player.jobNode->left : player.jobNode->right);
    }
    else
    {
        job();
        std::cout << "You have already chosen your job: " << player.jobNode->jobName << "\n";

        if (player.hasMeleeJob || player.hasRangeJob)
        {
            std::cout << "You need to reach level 3 to obtain the next job.\n";
        }
        pressAny();
    }
}

std::list<Item> playerInventory;
std::stack<std::string> travelHistory;
std::queue<Enemy> enemyQueue;
std::set<std::string> visitedLoc;
std::unordered_map<std::string, std::string> locDesc;

void route()
{
    std::cout << R"(
                Town
                 /\
           Forest  Castle ------
            /\                / \
        Cave  Mountain  Village  Savanna
         /\         \
   Desert  Swamp    Plain
    )" << std::endl;
}

void history(Node *&currentLocation)
{
    std::cout << "Current Location: " << currentLocation->location << std::endl;
    std::cout << "Previous Town: ";

    // Create a copy of the travelHistory stack
    std::stack<std::string> historyStack = travelHistory;

    // Print the travel history from the copy
    while (!historyStack.empty())
    {
        std::cout << historyStack.top();
        if (historyStack.size() > 1)
        {
            std::cout << " <- ";
        }
        historyStack.pop();
    }

    std::cout << std::endl;
    pressAny();
}

void travelProgress(Node *&currentLocation)
{
    int totalLocations = locDesc.size();
    int visitedLocations = visitedLoc.size() + 1;
    int unvisitedLocations = totalLocations - visitedLocations;

    double progress = (double)visitedLocations / totalLocations * 100;

    std::cout << "Travel Progress:\n";
    std::cout << "Current Location: " << currentLocation->location << "\n";

    std::cout << "Visited Locations: " << visitedLocations << "/" << totalLocations << " (" << progress << "%)\n";
    std::cout << "Remaining Unvisited Locations: " << unvisitedLocations << "\n\n";

    pressAny();
}

// Menyimpan peta dunia
Node *locationTree;

void createWorldMap()
{
    locationTree = new Node("Town");

    Node *castle = new Node("Castle", locationTree);
    Node *forest = new Node("Forest", locationTree);
    Node *cave = new Node("Cave", forest);
    Node *mountain = new Node("Mountain", forest);
    Node *village = new Node("Village", castle);
    Node *savanna = new Node("Savanna", castle);
    Node *desert = new Node("Desert", cave);
    Node *swamp = new Node("Swamp", cave);
    Node *plain = new Node("Plain", mountain);

    locationTree->children.push_back(forest);
    locationTree->children.push_back(castle);

    castle->children.push_back(village);
    castle->children.push_back(savanna);

    forest->children.push_back(cave);
    forest->children.push_back(mountain);

    cave->children.push_back(desert);
    cave->children.push_back(swamp);

    mountain->children.push_back(plain);

    locDesc["Town"] = "Evervale Town, pusat perdagangan dan komunitas yang ramai, tumbuh subur di tengah perbukitan yang tenang dan padang rumput yang hijau. Kota ini mengundang para petualang untuk mengungkap misteri yang tersembunyi di balik kisah masa lalunya.";
    locDesc["Forest"] = "Whispering Forest, hamparan dedaunan zamrud yang misterius, mengundang gumaman pelan roh-roh kuno yang menari di antara sinar matahari yang menembus kanopi.";
    locDesc["Castle"] = "Castle Evermere menjulang dengan megah dari lanskap yang subur, temboknya yang menjulang tinggi dan menara megahnya memberikan kehadiran yang luar biasa.";
    locDesc["Cave"] = "Shadowmire Cave, jaringan lorong-lorong bawah tanah yang labirin, mengundang dengan daya tarik yang menakutkan, pintu masuknya terselubung oleh sulur-sulur tanaman merambat dan kesuraman senja yang tidak menyenangkan.";
    locDesc["Mountain"] = "Frostpeak Mountain, sebuah gunung raksasa menjulang tinggi yang terselubung dalam hujan salju abadi, Lerengnya diselimuti pohon pinus kuno dan terselubung kabut.";
    locDesc["Village"] = "Oakhaven Village yang kuno, pesona pedesaan dan keindahan sederhananya merupakan surga bagi wisatawan yang lelah dan jiwa petualang. Jalanan berbatu yang berkelok-kelok berkelok-kelok melintasi jantung desa, dengan deretan pondok nyaman yang dihiasi kotak bunga berwarna-warni dan atap jerami.";
    locDesc["Savanna"] = "Serenwood Savanna yang belum terjamah. Di sini, ritme kehidupan berdetak selaras dengan daratan, saat kawanan makhluk agung berkeliaran dengan bebas di bawah langit yang luas.";
    locDesc["Desert"] = "Sunscar Desert, negeri dengan bukit pasir tak berujung dan panas yang berkilauan. Tebing batu pasir yang menjulang tinggi menjulang bagaikan penjaga kuno, menimbulkan bayangan panjang di atas dasar gurun.";
    locDesc["Swamp"] = "Mistwood Swamp yang penuh teka-teki. Di sini, daratan diselimuti kabut abadi, mengaburkan jalan di depan dan menyembunyikan rahasia kuno dan jahat. Saluran air yang berkelok-kelok membelah daerah berawa, perairannya yang gelap penuh dengan makhluk tak kasat mata dan legenda yang dibisikkan.";
}

void printLocationDescription(const std::string &loc)
{
    std::cout << "\n"
              << locDesc[loc] << std::endl;
}

void travelTo(Node *&currentLocation, const std::string &newLocation)
{
    if (currentLocation->location == newLocation)
    {
        std::cout << "\nYou are already in " << newLocation << "!\n\n";
        pressAny();
        return;
    }

    bool found = false;

    // First, check if the newLocation is a child of the currentLocation
    for (Node *children : currentLocation->children)
    {
        if (children->location == newLocation)
        {
            std::cout << "\n--- Traveling from " << currentLocation->location << " to " << newLocation << ". ---" << std::endl;

            printLocationDescription(newLocation);

            travelHistory.push(currentLocation->location);
            visitedLoc.insert(currentLocation->location);

            currentLocation = children;
            found = true;

            pressAny();
            return;
        }
    }

    // If not found, check if the newLocation is a parent of the currentLocation
    Node *temp = currentLocation->parent;
    if (temp->location == newLocation)
    {
        std::cout << "\n--- Traveling from " << currentLocation->location << " to " << newLocation << ". ---" << std::endl;

        printLocationDescription(newLocation);

        travelHistory.push(currentLocation->location);
        visitedLoc.insert(currentLocation->location);

        currentLocation = temp;
        found = true;

        pressAny();
        return;
    }

    if (!found)
    {
        std::cout << "--- Cannot travel from " << currentLocation->location << " to " << newLocation << " directly. ---" << std::endl;
        pressAny();
    }
}

void useItem(int index)
{
    if (index < 1 || index > playerInventory.size())
    {
        std::cout << "Invalid item index.\n";
        pressAny();
        return;
    }

    auto it = playerInventory.begin();
    std::advance(it, index - 1);

    if (it->quantity > 0)
    {
        int healAmount = it->value;
        playerHealth += healAmount;

        // Cap the playerHealth to 100
        if (playerHealth >= 100)
            playerHealth = 100;

        std::cout << "You used a " << it->name << " and restored " << healAmount << " health points.\n";
        std::cout << "Your current health: " << playerHealth << "\n";

        // Reduce the item quantity
        it->quantity--;
    }
    else
    {
        std::cout << "You don't have any " << it->name << " left.\n";
    }
    pressAny();
}

void showInventory()
{
    std::cout << "Player Level: " << player.level << ", XP: " << player.experience << "/" << player.maxExperience << ".\n\n";

    std::cout << "Player Inventory:\n";
    int index = 1;
    for (const auto &item : playerInventory)
    {
        std::cout << index << ". " << item.name << " (+" << item.value << " health) (Remaining: " << item.quantity << ")\n";
        index++;
    }
    std::cout << "\nEnter the item index to use, or 'x' to exit: ";

    std::string input;
    std::getline(std::cin, input);

    if (playerHealth >= 100 && input != "x")
    {
        std::cout << "Your health points is full\n";
        printf("\033[H\033[J");
        return;
    }

    if (input == "x")
    {
        printf("\033[H\033[J");
        return;
    }
    else
    {
        int itemIndex = std::stoi(input);
        useItem(itemIndex);
    }

    pressAny();
}

void playerAttack(Enemy &enemy)
{
    srand(time(nullptr));

    enemy.health -= 20;
    if (enemy.health < 0)
    {
        enemy.health = 0;
    }
    std::cout << "\nYou dealt 20 damage "
              << "(Enemy health: " << enemy.health << ")\n";

    if (enemy.health == 0)
    {
        int xpGained = rand() % 51 + 25; // between 25 and 75
        player.experience += xpGained;
        std::cout << "\nYou gained " << xpGained << " exp!\n";
    }

    // Check if the player has enough XP to level up
    while (player.experience >= player.maxExperience)
    {
        player.experience -= player.maxExperience;
        player.level++;
        player.maxExperience = static_cast<int>(player.maxExperience * 1.2);
        std::cout << "You leveled up to level " << player.level << "!\n\n";
    }
}

void playerTurn(Enemy &enemy)
{
    std::cout << "Player's turn:\n";
    std::cout << "1. Attack\n";
    std::cout << "2. Use Item\n";
    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;

    printf("\033[H\033[J");

    switch (choice)
    {
    case 1:
        playerAttack(enemy);
        break;
    case 2:
        showInventory();
        break;
    default:
        std::cout << "Invalid choice\n";
        break;
    }
}

void playerDefend(Enemy &enemy)
{
    if (enemy.health > 0)
    {
        playerHealth -= enemy.power;
        std::cout << enemy.name << " dealt " << enemy.power << " damage "
                  << "(Player health: " << playerHealth << ")\n\n";
    }
}

void generateEnemies(Node *currentLocation)
{
    enemyQueue = std::queue<Enemy>(); // Clear the existing enemyQueue

    srand(time(nullptr));

    // Generate random enemies
    int numEnemies = rand() % 4 + 1;
    for (int i = 0; i < numEnemies; i++)
    {
        std::string location = currentLocation->location;
        int health, power;
        if (location == "Forest" || location == "Cave" || location == "Swamp" || location == "Desert")
        {
            // Harder enemies
            health = rand() % 31 + 20; // Random health between 20 and 50
            power = rand() % 11 + 10;  // Random power between 10 and 20
        }
        else
        {
            // Easier enemies
            health = rand() % 11 + 10; // between 10 and 20
            power = rand() % 6 + 5;    // between 5 and 10
        }

        std::string enemyName = "Enemy " + std::to_string(i + 1);
        enemyQueue.push({enemyName, health, power});
    }
}

void fightEnemy(Node *currentLocation)
{
    generateEnemies(currentLocation);

    while (!enemyQueue.empty())
    {
        Enemy currentEnemy = enemyQueue.front();
        enemyQueue.pop();

        std::cout << "\n=== You are fighting " << currentEnemy.name << " (Health: " << currentEnemy.health << ")"
                  << " (Power " << currentEnemy.power << ") ===\n\n";

        while (currentEnemy.health > 0 && playerHealth > 0)
        {
            // Player turn's
            playerTurn(currentEnemy);

            // Enemy defeated
            if (currentEnemy.health <= 0)
            {
                std::cout << "You defeated " << currentEnemy.name << "!\n";
                std::cout << "Player Health: " << playerHealth << "\n";
            }

            // Enemy turn's
            playerDefend(currentEnemy);
            if (playerHealth <= 0)
            {
                std::cout << "You were defeated by " << currentEnemy.name << "!\n";
            }
        }
    }
    if (enemyQueue.empty())
        std::cout << "\nThere are no more enemies to fight.\n";
    pressAny();
}

int main()
{
    createWorldMap();
    Node *currentLocation = locationTree;

    // Menginisialisasi beberapa item dan musuh
    playerInventory.push_back({"Low Potion", 5, 100});
    playerInventory.push_back({"Medium Potion", 10, 100});
    playerInventory.push_back({"High Potion", 15, 100});
    playerInventory.push_back({"Meat", 5, 999});

    while (true)
    {
        std::cout << "\nWhat would you like to do?\n";
        std::cout << "1. Show Level and Inventory\n";
        std::cout << "2. Fight Enemy\n";
        std::cout << "3. Travel\n";
        std::cout << "4. Travel History\n";
        std::cout << "5. Travel Progress\n";
        std::cout << "6. Choose Job Class\n";
        std::cout << "7. Quit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        getchar();
        system("cls");

        switch (choice)
        {
        case 1:
            showInventory();
            break;
        case 2:
            fightEnemy(currentLocation);
            break;
        case 3:
        {
            route();
            std::cout << "Your location: " << currentLocation->location << "!\n";
            std::cout << "Enter the destination: ";
            std::string destination;
            std::cin >> destination;
            getchar();

            travelTo(currentLocation, destination);
            break;
        }
        case 4:
            history(currentLocation);
            break;
        case 5:
            travelProgress(currentLocation);
            break;
        case 6:
            chooseJob();
            break;
        case 7:
            std::cout << "Goodbye!\n";
            return 0;
        default:
            std::cout << "Invalid choice. Try again.\n";
            getchar();
            break;
        }
    }

    return 0;
}
