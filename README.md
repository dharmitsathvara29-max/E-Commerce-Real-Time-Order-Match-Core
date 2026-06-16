# E-Commerce-Real-Time-Order-Match-Core
# 🚚 ShipFast - E-Commerce Real-Time Order Match Core

## 📌 Overview

ShipFast is a Data Structures & Algorithms (DSA) based C++ project that simulates the backend order fulfillment system of a large-scale e-commerce platform such as Amazon or Flipkart.

The system manages inventory across multiple warehouses, processes customer orders, calculates taxes, prioritizes urgent shipments, finds optimal logistics routes, and intelligently allocates stock to minimize delivery cost and time.

This project demonstrates the practical application of core DSA concepts including Maps, Queues, Stacks, Priority Queues, Graphs, and Dijkstra's Algorithm in a real-world business scenario.

---

## 🎯 Problem Statement

Modern e-commerce platforms process thousands of orders every second. Existing systems face several challenges:

* Large inventory databases require efficient searching.
* Incorrect tax calculations must support rollback.
* Orders need strict checkout processing.
* Urgent shipments must be prioritized.
* Warehouses and transport routes need optimization.
* Order details should be retrievable instantly.
* Multi-item orders should be split intelligently across warehouses.

ShipFast addresses these challenges using efficient data structures and algorithms.

---

## ✨ Features

### 📦 Inventory Management

* Store and manage product inventory across warehouses.
* Fast product lookup using ordered indexing.
* Supports stock updates after order processing.

### 💰 Tax Calculation & Rollback

* Automatically calculates tax on orders.
* Maintains transaction history.
* Supports rollback using Stack data structure.

### 🛒 Checkout Processing

* Orders enter a FIFO checkout queue.
* Ensures fairness and preserves order submission sequence.

### 🔍 Order Lookup

* Retrieve order details instantly using Order ID.
* Uses indexed storage for efficient searching.

### 🚀 Shipping Priority System

* Prioritizes orders based on urgency:

  * NEXT_DAY
  * EXPRESS
  * STANDARD

### 🌍 Logistics Network

* Models warehouses and transport routes as a graph.
* Supports weighted routes representing distance/cost.

### ⚡ Shortest Path Optimization

* Uses Dijkstra's Algorithm to determine optimal logistics paths.
* Calculates minimum transportation cost between warehouses.

### 📦 Smart Stock Splitter

* Allocates products from the most suitable warehouse.
* Supports multi-warehouse fulfillment for large orders.

---

## 🧠 Data Structures Used

| Feature           | Data Structure         |
| ----------------- | ---------------------- |
| Inventory Index   | map                    |
| Tax Rollback      | stack                  |
| Checkout Line     | queue                  |
| Order Lookup      | map                    |
| Shipping Priority | priority_queue         |
| Logistics Network | Graph (Adjacency List) |
| Shortest Path     | Dijkstra Algorithm     |
| Stock Allocation  | Greedy Selection       |

---

## 🏗️ System Architecture

ShipFast consists of the following modules:

### Inventory Module

Maintains stock information for all warehouses.

### Tax Module

Calculates taxes and supports rollback functionality.

### Checkout Module

Processes customer orders in FIFO order.

### Shipping Module

Ranks orders according to shipping urgency.

### Logistics Module

Represents warehouses and transport connections.

### Route Optimization Module

Calculates shortest delivery routes using Dijkstra's Algorithm.

### Stock Splitter Module

Selects the most suitable warehouse for each product.

---

## ⚙️ Algorithms Implemented

### 1. Inventory Indexing

* Ordered product storage using map.
* Efficient searching and retrieval.

### 2. Tax Rollback

* Stack-based undo mechanism.

### 3. FIFO Checkout Processing

* Queue-based customer order processing.

### 4. Shipping Prioritization

* Priority Queue based scheduling.

### 5. Logistics Graph

* Adjacency List representation.

### 6. Dijkstra's Algorithm

* Finds shortest warehouse route.

### 7. Greedy Warehouse Selection

* Chooses warehouse with minimum delivery cost.

---

## 📊 Complexity Analysis

| Operation                | Time Complexity  |
| ------------------------ | ---------------- |
| Add Inventory            | O(log n)         |
| Search Inventory         | O(log n)         |
| Tax Calculation          | O(1)             |
| Tax Rollback             | O(1)             |
| Add Order                | O(1)             |
| Order Lookup             | O(log n)         |
| Shipping Priority Insert | O(log n)         |
| Add Route                | O(1)             |
| Dijkstra Shortest Path   | O((V + E) log V) |
| Stock Allocation         | O(w)             |

Where:

* n = Number of orders/products
* V = Number of warehouses
* E = Number of transport routes
* w = Warehouses containing stock

## 💻 Technologies Used

* C++
* STL (Standard Template Library)
* Queue
* Stack
* Map
* Priority Queue
* Graph Algorithms
* Dijkstra's Algorithm
Sample Workflow

1. Add inventory to warehouses.
2. Create logistics routes.
3. Add customer orders.
4. Lookup order details.
5. Process orders.
6. Calculate tax.
7. Allocate stock.
8. Rollback tax if needed.
9. View updated inventory.

How it Starts by adding the data
<img width="283" height="716" alt="Screenshot 2026-06-17 at 12 11 55 AM" src="https://github.com/user-attachments/assets/fe3b2bca-8aa1-46c2-bf8e-ffc1d8058260" />
And after adding all the data by our choice the main output
<img width="423" height="182" alt="Screenshot 2026-06-17 at 12 12 31 AM" src="https://github.com/user-attachments/assets/6068c6dc-d9cb-4d26-bd4e-cbb50e0ed44d" />


Real-World Relevance

The architecture of ShipFast reflects concepts used in modern e-commerce platforms such as:

* Amazon Fulfillment Network
* Flipkart Supply Chain
* Walmart Logistics Systems

The project demonstrates how DSA concepts directly solve real-world order fulfillment and logistics challenges.
 Learning Outcomes
Through this project, the following concepts were implemented and understood:
* Maps and Ordered Indexing
* Queues and FIFO Processing
* Stack-based Undo Systems
* Priority Scheduling
* Graph Representation
* Dijkstra's Shortest Path Algorithm
* Greedy Optimization
* Real-world System Design using DSA
