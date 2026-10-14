#include <iostream>
#include <random>
#include <vector>
#include <iomanip>
using namespace std;

struct CustomerRecord
{
    int id;
    double interArrivalTime;
    double arrivalTime;
    double serviceTime;
    double serviceStartTime;
    double waitingTime;
    double serviceEndTime;
};

//running queue simulation
void Simulation(int customers,double MinArrival, double MaxArrival,double MinService,double MaxService)
{
random_device rd; //random number seed generator
    mt19937 gen(rd());
    uniform_real_distribution<double> arrivalDist (MinArrival,MaxArrival);
    uniform_real_distribution<double> ServiceDist (MinService,MaxService);

    vector<CustomerRecord> records;
    double previousArrivalTime = 0.0;
    double previousServiceEndTime = 0.0;
    double totalWaitTime = 0.0;

    //running loop for all customers
    for (int i= 1;i <= customers ; i++)
    {
        CustomerRecord c;
        c.id = i;
        c.interArrivalTime = arrivalDist(gen);
        c.serviceTime = ServiceDist(gen);

        //calculating arrival and service time
        c.arrivalTime = (i==1) ? c.interArrivalTime : previousArrivalTime + c.interArrivalTime;
        c.serviceStartTime = (i==1) ? c.arrivalTime : max(c.arrivalTime,previousServiceEndTime);
        c.waitingTime = c.serviceStartTime - c.arrivalTime;
        c.serviceEndTime = c.serviceStartTime + c.serviceTime;

        totalWaitTime+=c.waitingTime;

        //save
        records.push_back(c);

        previousArrivalTime= c.arrivalTime;
        previousServiceEndTime= c.serviceEndTime;

    }

    //simulation output table
    cout << "Simulation table" << endl;
    cout << setw(10) << "Customer"
         << setw(15) << "Inter-Arrival"
         << setw(15) << "Arrival Time"
         << setw(15) << "Service Time"
         << setw(15) << "Start Time"
         << setw(15) << "Wait Time"
         << setw(15) << "End Time" << endl;
    cout << string(100, '-') << endl;

    for (const auto &c : records) {
        cout << setw(10) << c.id
             << setw(15) << fixed << setprecision(2) << c.interArrivalTime
             << setw(15) << c.arrivalTime
             << setw(15) << c.serviceTime
             << setw(15) << c.serviceStartTime
             << setw(15) << c.waitingTime
             << setw(15) << c.serviceEndTime << endl;
    }

    cout << "Queue statistics" << endl;
    cout << "Total Customers Processed: " << customers << endl;
    cout << "Average Waiting Time: " << (totalWaitTime / customers) << " minutes" << endl;
    cout << "Total Time in System: " << previousServiceEndTime << " minutes" << endl;
}
int main()
{
    //default values
    int customers = 100;
    //arrival time
    double MinArrival = 1.0;
    double MaxArrival = 5.0;

    //service times
    double MinService = 1.0;
    double MaxService = 6.0;

    //input of data
    cout<<"Enter number of customers"<<endl;
    cin>>customers;
    cout<<"Enter minimum and maximum  arrival times"<<endl;
    cin>>MinArrival>>MaxArrival;
    cout<<"Enter minimum and maximum  service times"<<endl;
    cin>>MinService>>MaxService;

    cout<<"input successfully recorded"<<endl;

    Simulation(customers,MinArrival,MaxArrival,MinService,MaxService);
    return 0;

}
