// a1234567, Stark, Tony
// a2345678, Rogers, Steve
// a3456789, Banner, Bruce
// avengers
/*
created by Andrey Kan
andrey.kan@adelaide.edu.au
2021
*/
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

// s a namespace: https://www.cplusplus.com/doc/oldtutorial/namespaces/
const int Q1_TIME_ALLOWANCE = 8; // allow to use up to this number of time slots at once
const int Q2_TIME_ALLOWANCE = 16;
const int PRINT_LOG = 0; // print detailed execution trace

class Customer
{
public:
    string name;
    int priority;
    int arrival_time;
    int slots_remaining; // how many time slots are still needed
    int playing_since;

    Customer(string par_name, int par_priority, int par_arrival_time, int par_slots_remaining)
    {
        name = par_name;
        priority = par_priority;
        arrival_time = par_arrival_time;
        slots_remaining = par_slots_remaining;
        playing_since = -1;
    }
};

class Event
{
public:
    int event_time;
    int customer_id; // each event involes exactly one customer

    Event(int par_event_time, int par_customer_id)
    {
        event_time = par_event_time;
        customer_id = par_customer_id;
    }
};

void initialize_system(
    ifstream &in_file,
    deque<Event> &arrival_events,
    vector<Customer> &customers)
{
    string name;
    int priority, arrival_time, slots_requested;

    // read input file line by line
    // https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
    int customer_id = 0;
    while (in_file >> name >> priority >> arrival_time >> slots_requested)
    {
        Customer customer_from_file(name, priority, arrival_time, slots_requested);
        customers.push_back(customer_from_file);

        // new customer arrival event
        Event arrival_event(arrival_time, customer_id);
        arrival_events.push_back(arrival_event);

        customer_id++;
    }
}

void print_state(
    ofstream &out_file,
    int current_time,
    int current_id,
    const deque<Event> &arrival_events,
    const deque<int> &customer_queue)
{
    out_file << current_time << " " << current_id << '\n';
    if (PRINT_LOG == 0)
    {
        return;
    }
    cout << current_time << ", " << current_id << '\n';
    for (int i = 0; i < arrival_events.size(); i++)
    {
        cout << "\t" << arrival_events[i].event_time << ", " << arrival_events[i].customer_id << ", ";
    }
    cout << '\n';
    for (int i = 0; i < customer_queue.size(); i++)
    {
        cout << "\t" << customer_queue[i] << ", ";
    }
    cout << '\n';
}

struct custom_sort
{
    bool operator()(const pair<int, int> &left, const pair<int, int> &right)
    {
        return left.second < right.second;
    }
};

deque<int> SJF(deque<int> queue, vector<Customer> &customers)
{
    deque<int> return_queue;
    vector<pair<int, int> > vec;

    for (int i = 0; i < queue.size(); i++)
    {
        vec.push_back(make_pair(queue[i], customers[queue[i]].slots_remaining));
    }

    sort(vec.begin(), vec.end(), custom_sort());

    for (int i = 0; i < vec.size(); i++)
    {
        return_queue.push_back(vec[i].first);
    }

    return return_queue;
}
// process command line arguments
// https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Provide input and output file names." << endl;
        return -1;
    }
    ifstream in_file(argv[1]);
    ofstream out_file(argv[2]);
    if ((!in_file) || (!out_file))
    {
        cerr << "Cannot open one of the files." << endl;
        return -1;
    }

    // deque: https://www.geeksforgeeks.org/deque-cpp-stl/
    // vector: https://www.geeksforgeeks.org/vector-in-cpp-stl/
    deque<Event> arrival_events; // new customer arrivals
    vector<Customer> customers;  // information about each customer

    // read information from file, initialize events queue
    initialize_system(in_file, arrival_events, customers);

    int current_id = -1;      // who is using the machine now, -1 means nobody
    int time_out = -1;        // time when current customer will be preempted
    deque<int> queue;         // waiting queue
    deque<int> queue2;

    // step by step simulation of each time slot
    bool all_done = false;
    for (int current_time = 0; !all_done; current_time++)
    {
        // welcome newly arrived customers
        while (!arrival_events.empty() && (current_time == arrival_events[0].event_time))
        {
            queue.push_back(arrival_events[0].customer_id);
            arrival_events.pop_front();
        }
        // check if we need to take a customer off the machine
        if (current_id >= 0)
        {
            if (current_time == time_out)
            {
                int last_run = current_time - customers[current_id].playing_since;
                customers[current_id].slots_remaining -= last_run;
                if (customers[current_id].slots_remaining > 0)
                {
                    queue2.push_back(current_id);
                    queue2 = SJF(queue2, customers);
                }
                current_id = -1; // the machine is free now
            }
        }
        // if machine is empty, schedule a new customer
        if (current_id == -1)
        {
            if (!queue.empty()) // is anyone waiting?
            {
                current_id = queue.front();
                queue.pop_front();
                if (Q1_TIME_ALLOWANCE > customers[current_id].slots_remaining)
                {
                    time_out = current_time + customers[current_id].slots_remaining;
                }
                else
                {
                    time_out = current_time + Q1_TIME_ALLOWANCE;
                }
                customers[current_id].playing_since = current_time;
            }
            else if (!queue2.empty())
            {
                current_id = queue2.front();
                queue2.pop_front();
                if (Q2_TIME_ALLOWANCE > customers[current_id].slots_remaining)
                {
                    time_out = current_time + customers[current_id].slots_remaining;
                }
                else
                {
                    time_out = current_time + Q2_TIME_ALLOWANCE;
                }
                customers[current_id].playing_since = current_time;
            }
        }
        print_state(out_file, current_time, current_id, arrival_events, queue);

        // exit loop when there are no new arrivals, no waiting and no playing customers
        all_done = (arrival_events.empty() && queue.empty() && (current_id == -1));
    }

    return 0;
}
