#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <queue>
#include <stack>
#include <limits>
#include <climits>
#include <algorithm>

using namespace std;

/* =========================================================
   SHIPFAST - FINAL DSA CASE STUDY
========================================================= */

/* =========================================================
                    ORDER STRUCTURE
========================================================= */

struct Order {
    string id;
    vector<string> items;
    string type;
    double amount;
    int priority;

    Order() {}

    Order(string i, vector<string> it, string t, double a) {
        id = i;
        items = it;
        type = t;
        amount = a;

        if (t == "EXPRESS")
            priority = 3;
        else if (t == "NEXT_DAY")
            priority = 2;
        else
            priority = 1;
    }
};

/* =========================================================
                    INVENTORY INDEX
========================================================= */

class InventoryIndex {
public:

    // item -> [(warehouse, quantity)]
    map<string, vector<pair<int, int>>> index;

    void addStock(int warehouse,
                  const string &item,
                  int qty)
    {
        index[item].push_back({warehouse, qty});
    }

    int getRemainingStock(int warehouse,
                          const string &item)
    {
        if(index.find(item) == index.end())
            return 0;

        for(auto &p : index[item])
        {
            if(p.first == warehouse)
                return p.second;
        }

        return 0;
    }

    bool reduceStock(int warehouse,
                     const string &item,
                     int qty)
    {
        if(index.find(item) == index.end())
            return false;

        for(auto &p : index[item])
        {
            if(p.first == warehouse &&
               p.second >= qty)
            {
                p.second -= qty;
                return true;
            }
        }

        return false;
    }

    void displayInventory()
    {
        cout << "\n=================================\n";
        cout << "FINAL INVENTORY REPORT\n";
        cout << "=================================\n";

        map<int, vector<pair<string,int>>> warehouseView;

        for(auto &itemEntry : index)
        {
            for(auto &warehouseEntry :
                itemEntry.second)
            {
                warehouseView[warehouseEntry.first]
                .push_back({
                    itemEntry.first,
                    warehouseEntry.second
                });
            }
        }

        for(auto &w : warehouseView)
        {
            cout << "\nWarehouse "
                 << w.first
                 << endl;

            for(auto &item : w.second)
            {
                cout << "  "
                     << item.first
                     << " : "
                     << item.second
                     << endl;
            }
        }
    }
};

/* =========================================================
                    TAX SYSTEM
========================================================= */

struct TaxRecord {
    string orderId;
    double originalAmount;
    double finalAmount;
};

class TaxSystem {
public:

    stack<TaxRecord> history;

    double applyTax(const string &orderId,
                    double amount)
    {
        double finalAmount =
            amount * 1.18;

        history.push({
            orderId,
            amount,
            finalAmount
        });

        return finalAmount;
    }

    void rollback()
    {
        if(history.empty())
        {
            cout << "\nNo transactions available for rollback.\n";
            return;
        }

        TaxRecord last =
            history.top();

        history.pop();

        cout << "\n========== TAX ROLLBACK ==========\n";

        cout << "Order ID        : "
             << last.orderId
             << endl;

        cout << "Original Amount : "
             << last.originalAmount
             << endl;

        cout << "Taxed Amount    : "
             << last.finalAmount
             << endl;
    }
};
/* =========================================================
                    GRAPH (LOGISTICS MAP)
========================================================= */

class Graph {
public:

    unordered_map<int,
        vector<pair<int,int>>> adj;

    void addEdge(int u,
                 int v,
                 int w)
    {
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    vector<int> dijkstra(int src,
                         int n)
    {
        vector<int> dist(n, INT_MAX);

        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;

        dist[src] = 0;

        pq.push({0, src});

        while(!pq.empty())
        {
            auto current = pq.top();
            pq.pop();

            int d = current.first;
            int node = current.second;

            if(d > dist[node])
                continue;

            for(auto &nbr : adj[node])
            {
                int nextNode = nbr.first;
                int weight = nbr.second;

                if(dist[nextNode] >
                   dist[node] + weight)
                {
                    dist[nextNode] =
                        dist[node] + weight;

                    pq.push({
                        dist[nextNode],
                        nextNode
                    });
                }
            }
        }

        return dist;
    }
};

/* =========================================================
                    ORDER SYSTEM
========================================================= */

struct CompareOrder {

    bool operator()(const Order &a,
                    const Order &b) const
    {
        return a.priority < b.priority;
    }
};

class OrderSystem {
public:
queue<Order> checkoutQueue;

priority_queue<
    Order,
    vector<Order>,
    CompareOrder
> shippingQueue;

    map<string, Order> orderDatabase;

    void addOrder(const Order &o)
    {
        checkoutQueue.push(o);
        orderDatabase[o.id] = o;
    }
void prepareShipping()
{
    while(!checkoutQueue.empty())
    {
        shippingQueue.push(
            checkoutQueue.front()
        );

        checkoutQueue.pop();
    }
}
bool shippingEmpty()
{
    return shippingQueue.empty();
}
Order nextShippingOrder()
{
    Order o =
        shippingQueue.top();

    shippingQueue.pop();

    return o;
}
    
    void lookupOrder(const string &id)
    {
        cout << "\n========== ORDER LOOKUP ==========\n";

        if(orderDatabase.find(id)
           == orderDatabase.end())
        {
            cout << "Order not found.\n";
            return;
        }

        Order o =
            orderDatabase[id];

        cout << "Order ID : "
             << o.id
             << endl;

        cout << "Type     : "
             << o.type
             << endl;

        cout << "Amount   : "
             << o.amount
             << endl;

        cout << "Items    : ";

        for(auto &item : o.items)
        {
            cout << item << " ";
        }

        cout << endl;
    }
};
/* =========================================================
                FULFILLMENT ENGINE
========================================================= */

class FulfillmentEngine {
private:

    InventoryIndex &inventory;
    Graph &graph;

public:

    FulfillmentEngine(
        InventoryIndex &inv,
        Graph &g
    ) : inventory(inv), graph(g) {}

    int bestWarehouse(
        const string &item,
        const vector<int> &dist
    )
    {

        if(inventory.index.find(item)
           == inventory.index.end())
            return -1;

        int best = -1;
        int bestCost = INT_MAX;

        cout << "\nEvaluating Item: "
             << item
             << endl;

        for(auto &entry :
            inventory.index[item])
        {
            int warehouse =
                entry.first;

            int stock =
                entry.second;

            if(stock <= 0)
                continue;

            int distanceCost =
                dist[warehouse];

            int stockPenalty =
                max(0, 10 - stock);

            int totalCost =
                distanceCost +
                stockPenalty;

            cout
                << "Warehouse "
                << warehouse
                << " | Distance="
                << distanceCost
                << " | Stock="
                << stock
                << " | Penalty="
                << stockPenalty
                << " | TotalCost="
                << totalCost
                << endl;

            if(totalCost < bestCost)
            {
                bestCost = totalCost;
                best = warehouse;
            }
        }

        if(best != -1)
        {
            cout
                << "Selected Warehouse: "
                << best
                << endl;
        }

        return best;
    }

    void processOrder(
        const Order &order,
        const vector<int> &dist
    )
    {

        cout << "\n=================================\n";
        cout << "Processing Order: "
             << order.id
             << endl;

        cout << "Priority Level : "
             << order.priority
             << endl;

        cout << "=================================\n";

        for(auto &item :
            order.items)
        {

            int warehouse =
                bestWarehouse(
                    item,
                    dist
                );

            if(warehouse == -1)
            {
                cout
                    << "Item "
                    << item
                    << " OUT OF STOCK"
                    << endl;

                continue;
            }

            inventory.reduceStock(
                warehouse,
                item,
                1
            );

            cout
                << "Item: "
                << item
                << " | Warehouse: "
                << warehouse
                << " | Remaining Stock: "
                << inventory.getRemainingStock(
                       warehouse,
                       item
                   )
                << endl;
        }
    }
};

/* =========================================================
                        MAIN
========================================================= */
int main()
{
    InventoryIndex inventory;
    TaxSystem taxSystem;
    Graph logistics;
    OrderSystem orderSystem;
    FulfillmentEngine engine(
        inventory,
        logistics
    );

    int choice;

    do
    {
        cout << "\n=============================\n";
        cout << "SHIPFAST MANAGEMENT SYSTEM\n";
        cout << "=============================\n";
        cout << "1. Add Inventory\n";
        cout << "2. Add Logistics Route\n";
        cout << "3. Add Order\n";
        cout << "4. Order Lookup\n";
        cout << "5. Process Orders\n";
        cout << "6. Tax Rollback\n";
        cout << "7. Show Inventory\n";
        cout << "0. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                int warehouse;
                string item;
                int qty;
      

                cout << "\nWarehouse ID: ";
                cin >> warehouse;

                cout << "Item Name: ";
                cin >> item;

                cout << "Quantity: ";
                cin >> qty;

                inventory.addStock(
                    warehouse,
                    item,
                    qty
                );

                cout << "Inventory Added!\n";
                break;
            }

            case 2:
            {
                int u,v,w;
               

                cout << "\nSource Warehouse: ";
                cin >> u;

                cout << "Destination Warehouse: ";
                cin >> v;

                cout << "Distance/Cost: ";
                cin >> w;

                logistics.addEdge(
                    u,
                    v,
                    w
                );

                cout << "Route Added!\n";
                break;
            }

            case 3:
            {
                string id;
                string type;
                double amount;

                int n;

                vector<string> items;

                cout << "\nOrder ID: ";
                cin >> id;

                cout << "Order Type (EXPRESS/NEXT_DAY/STANDARD): ";
                cin >> type;

                cout << "Amount: ";
                cin >> amount;

                cout << "Number of Items: ";
                cin >> n;

                for(int i=0;i<n;i++)
                {
                    string item;

                    cout << "Item "
                         << i+1
                         << ": ";

                    cin >> item;

                    items.push_back(item);
                }

                orderSystem.addOrder(
                    Order(
                        id,
                        items,
                        type,
                        amount
                    )
                );

                cout << "Order Added!\n";

                break;
            }

            case 4:
            {
                string id;

                cout << "\nEnter Order ID: ";
                cin >> id;

                orderSystem.lookupOrder(id);

                break;
            }

            case 5:
            {
                int totalWarehouses;

                cout << "\nEnter Number Of Warehouses: ";
                cin >> totalWarehouses;

                vector<int> dist =
                    logistics.dijkstra(
                        0,
                        totalWarehouses
                    );

                orderSystem.prepareShipping();

while(
    !orderSystem.shippingEmpty()
)
{
    Order current =
        orderSystem.nextShippingOrder();
                    double finalAmount =
                        taxSystem.applyTax(
                            current.id,
                            current.amount
                        );

                    engine.processOrder(
                        current,
                        dist
                    );

                    cout
                        << "Final Amount: "
                        << finalAmount
                        << endl;
                }

                break;
            }

            case 6:
            {
                taxSystem.rollback();
                break;
            }

            case 7:
            {
                inventory.displayInventory();
                break;
            }

            case 0:
            {
                cout << "\nExiting...\n";
                break;
            }

            default:
            {
                cout << "\nInvalid Choice!\n";
            }
        }

    } while(choice != 0);

    return 0;
}