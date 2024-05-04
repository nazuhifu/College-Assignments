#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

int playerHealth = 100;

// Struct untuk menyimpan item
struct Item
{
    std::string name;
    int value;
};

// Struct untuk menyimpan data musuh
struct Enemy
{
    std::string name;
    int health;
    int power;
};

struct Node
{
    std::string location;
    std::vector<Node *> neighbor;

    Node(const std::string &loc) : location(loc) {} // Constructor
};

std::list<Item> playerInventory;
std::stack<std::string> travelHistory;
std::queue<Enemy> enemyQueue;
std::set<std::string> visitedLoc;
std::unordered_map<std::string, std::string> locDesc;

void pressAny()
{
    std::cout << "\nPress any key to continue... ";
    getchar(); // Wait for a key press
    system("cls");
}

void route()
{
    std::cout << R"(
                Town
                 /\
           Forest  Castle ---------
            /\                 /   \
        Cave  Mountain --- Village  Savanna
         /\
   Desert  Swamp
    )" << std::endl;
}

void history(Node *&currentLocation)
{
    std::cout << "Current Location: " << currentLocation->location << std::endl;
    std::cout << "Travel History: ";

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
Node *worldMap;

void createWorldMap()
{
    worldMap = new Node("Town");
    Node *castle = new Node("Castle");
    Node *forest = new Node("Forest");
    Node *cave = new Node("Cave");
    Node *mountain = new Node("Mountain");
    Node *village = new Node("Village");
    Node *savanna = new Node("Savanna");
    Node *desert = new Node("Desert");
    Node *swamp = new Node("Swamp");

    worldMap->neighbor.push_back(forest);
    worldMap->neighbor.push_back(castle);

    castle->neighbor.push_back(worldMap);
    castle->neighbor.push_back(village);
    castle->neighbor.push_back(savanna);

    forest->neighbor.push_back(worldMap);
    forest->neighbor.push_back(cave);
    forest->neighbor.push_back(mountain);

    cave->neighbor.push_back(forest);
    cave->neighbor.push_back(desert);
    cave->neighbor.push_back(swamp);

    mountain->neighbor.push_back(forest);
    mountain->neighbor.push_back(village);

    village->neighbor.push_back(mountain);
    village->neighbor.push_back(castle);

    savanna->neighbor.push_back(castle);
    desert->neighbor.push_back(cave);
    swamp->neighbor.push_back(cave);

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
        std::cout << "You are already in " << newLocation << "!\n\n";
        pressAny();
        return;
    }

    bool found = false;

    for (Node *neighbor : currentLocation->neighbor)
    {
        if (neighbor->location == newLocation)
        {
            std::cout << "--- Traveling from " << currentLocation->location << " to " << newLocation << ". ---" << std::endl;

            printLocationDescription(newLocation);

            travelHistory.push(currentLocation->location);
            visitedLoc.insert(currentLocation->location);

            currentLocation = neighbor;
            found = true;
            pressAny();
            return;
        }
    }

    if (!found)
    {
        std::cout << "--- Cannot travel from " << currentLocation->location << " to " << newLocation << " directly. ---" << std::endl;
        pressAny();
    }
}

void showInventory()
{
    std::cout << "Player Inventory:\n";
    for (const auto &item : playerInventory)
    {
        std::cout << "- " << item.name << " (Value: " << item.value << ")\n";
    }
    pressAny();
}

void playerAttack(Enemy &enemy)
{
    enemy.health -= 20;
    if (enemy.health < 0)
    {
        enemy.health = 0;
    }
    std::cout << "You dealt 20 damage "
              << "(Enemy health: " << enemy.health << ")\n";
}

void playerDefend(Enemy &enemy)
{
    if (enemy.health > 0)
    {
        playerHealth -= enemy.power;
        std::cout << enemy.name << " dealt " << enemy.power << " damage "
                  << "(Player health: " << playerHealth << ")\n";
    }
}

void fightEnemy()
{
    if (!enemyQueue.empty())
    {
        Enemy currentEnemy = enemyQueue.front();
        enemyQueue.pop();

        std::cout << "\nYou are fighting " << currentEnemy.name << " (Health: " << currentEnemy.health << ")"
                  << " (Power " << currentEnemy.power << ")\n\n";

        while (currentEnemy.health > 0)
        {
            // Player turn's
            playerAttack(currentEnemy);

            // Enemy defeated
            if (currentEnemy.health <= 0)
            {
                std::cout << "You defeated " << currentEnemy.name << "!\n";
                std::cout << "\n--- Player Health: " << playerHealth << " ---\n";
            }

            // Enemy turn's
            playerDefend(currentEnemy);
            if (playerHealth <= 0)
            {
                std::cout << "You were defeated by " << currentEnemy.name << "!\n";
            }
        }
    }
    else
    {
        std::cout << "There are no enemies to fight.\n";
    }
    pressAny();
}

int main()
{
    createWorldMap();
    Node *currentLocation = worldMap;

    // Menginisialisasi beberapa item dan musuh
    playerInventory.push_back({"Low Potion", 5});
    playerInventory.push_back({"Medium Potion", 10});
    playerInventory.push_back({"High Potion", 15});
    playerInventory.push_back({"Meat", 5});

    enemyQueue.push({"Goblin", 30, 5});
    enemyQueue.push({"Orc", 50, 10});
    enemyQueue.push({"Werewolf", 50, 15});
    enemyQueue.push({"Ogre", 55, 15});

    while (true)
    {
        std::cout << "What would you like to do?\n";
        std::cout << "1. Show Inventory\n";
        std::cout << "2. Fight Enemy\n";
        std::cout << "3. Travel\n";
        std::cout << "4. Travel History\n";
        std::cout << "5. Travel Progress\n";
        std::cout << "6. Quit\n";
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
            fightEnemy();
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