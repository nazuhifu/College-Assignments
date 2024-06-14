#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

struct Edge
{
    int dest;
    int weight;
};

struct Graph
{
    int V;
    unordered_map<int, vector<Edge>> adj;
};

// Fungsi untuk menambahkan edge ke graph
void addEdge(Graph &graph, int src, int dest, int weight)
{
    graph.adj[src].push_back({dest, weight});
    graph.adj[dest].push_back({src, weight});
}

// Implementasi Quick Sort
int partition(vector<string> &cities, int low, int high)
{
    string pivot = cities[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (cities[j] < pivot)
        {
            i++;
            swap(cities[i], cities[j]);
        }
    }
    swap(cities[i + 1], cities[high]);
    return (i + 1);
}

void quickSort(vector<string> &cities, int low, int high)
{
    if (low < high)
    {
        int pi = partition(cities, low, high);
        quickSort(cities, low, pi - 1);
        quickSort(cities, pi + 1, high);
    }
}

// Implementasi Binary Search
int binarySearch(vector<string> &cities, string target)
{
    int low = 0, high = cities.size() - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (cities[mid] == target)
            return mid;
        if (cities[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // Jika tidak ditemukan
}

// Implementasi Dijkstra untuk mencari jalan terpendek
vector<int> dijkstra(const Graph &graph, int src)
{
    vector<int> dist(graph.V, INT_MAX);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (auto &edge : graph.adj.at(u))
        {
            int v = edge.dest;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main()
{
    Graph graph;
    graph.V = 5;
    vector<string> cities = {"London", "Bristol", "Manchester", "Liverpool", "Birmingham"};

    addEdge(graph, 0, 1, 2); // London ke Bristol
    addEdge(graph, 0, 2, 4); // London ke Manchester
    addEdge(graph, 1, 2, 1); // Bristol ke Manchester
    addEdge(graph, 1, 3, 7); // Bristol ke Liverpool
    addEdge(graph, 2, 4, 3); // Manchester ke Birmingham

    cout << "Daftar kota: \n";
    cout << "0. London\n";
    cout << "1. Bristol\n";
    cout << "2. Manchester\n";
    cout << "3. Liverpool\n";
    cout << "4. Birmingham\n\n";

    int opsi;
    cout << "Pilih opsi program:\n";
    cout << "1. Cari indeks kota terurut.\n";
    cout << "2. Cari jarak terdekat.\n";
    cout << "Pilih opsi (1-2): ";
    cin >> opsi;
    getchar();

    string target;
    int index;
    int source;
    vector<int> distances;

    switch (opsi)
    {
    case 1:
        // Sort kota-kota menggunakan Quick Sort
        quickSort(cities, 0, cities.size() - 1);

        cout << endl;
        cout << "Cari indeks kota secara terurut\n";
        cout << "Input nama kota: ";
        cin >> target;
        getchar();

        // Cari kota menggunakan Binary Search
        index = binarySearch(cities, target);
        if (index != -1)
        {
            cout << "Kota " << target << " ditemukan di indeks " << index << endl;
        }
        else
        {
            cout << "Kota " << target << " tidak ditemukan" << endl;
        }

        cout << endl;

        break;

    case 2:
        // Cari jalan terpendek
        cout << "Input indeks kota awal: ";
        cin >> source;

        distances = dijkstra(graph, source);
        cout << endl;
        cout << "Jarak terpendek dari " << cities[source] << " ke kota-kota lain:" << endl;
        for (int i = 0; i < graph.V; i++)
        {
            cout << "Ke " << cities[i] << ": " << distances[i] << endl;
        }
        break;

    default:
        break;
    }

    return 0;
}
