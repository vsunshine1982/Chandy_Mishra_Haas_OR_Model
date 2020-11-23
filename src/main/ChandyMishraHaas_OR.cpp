//============================================================================
// Name        : ChandyMishraHaas_OR.cpp
// Author      : Vivek Malhotra
// Version     : 0.0.003
// Copyright   : 
// Description : Chandy–Misra–Haas Algorithm for the OR model, Ansi-style
//============================================================================

# include <iostream>
# include <stdio.h>
# include <vector>
# include <string>
# include <queue>

using namespace std;

void engage_query(vector<vector<int> > graph, int init, int dest);

void disp_graph(vector<vector<int> > mat);

void reply_query(vector<vector<int> > graph, int init, int dest);

int no_of_process;
vector<bool> wait_msg;
vector<int> msg_count;

int no_of_deadlocks = 0;
int no_of_knots = 0;

bool deadlock_flag = 0;

int main() {

	int probe_pid;

	int sites = 0;
	cout << "Enter number of sites (Minimum value greater than 1):" << endl;
	cin >> sites;

	for (int i = 0; i < sites; i++) {
		int temp;
		cout << "Enter number of processes for site" << (i+1) << ": (Minimum value greater than 1)";
		cin >> temp;
		no_of_process += temp;
	}

	cout << "Total number of sites = " << sites <<"; Total number of processes = " << no_of_process;

	if (no_of_process > 1) {
		cout << "Enter the wait graph for processes; Enter 1 if the process is dependent and 0 if not." << endl;

		vector<vector<int> > wait_graph(no_of_process);
		wait_msg.assign(no_of_process, false);
		msg_count.assign(no_of_process, 0);

		for (int from = 0; from < no_of_process; from++) {
			for (int to = 0; to < no_of_process; to++) {
				int temp;
				cout << "From Process "<< (from+1) <<" to : "<<(to+1)<<"(1/0) :"<<endl;
				cin >> temp;
				wait_graph.at(from).push_back(temp);
			}
		}

		cout << endl;

		cout << "The wait-for graph is: " << endl;
		disp_graph(wait_graph);
		cout << endl;

		cout << "Enter the process initiating the probe (Between 1 and no_of_process): " << endl;
		cin >> probe_pid;
		cout << endl;
		probe_pid = probe_pid + 1;

		cout << "Initiating probe..."<<endl<<endl;
		cout << "DIRECTION \t PROBE \t MESSAGES \t WAIT_FLAG"<<endl;

		for (int col = 0; col < no_of_process; col++) {
			if (wait_graph.at(probe_pid).at(col) == 1) {
				cout << " S" << (probe_pid + 1) << " --> S" << (col + 1) << "     (" << (probe_pid + 1) << "," << (probe_pid + 1) << "," << (col + 1) << ")" << " , \t"<< wait_msg[probe_pid]<<" , \t"<<msg_count[probe_pid]<<endl;
				engage_query(wait_graph, probe_pid, col);
			}
		}

		cout<<"Number of deadlocks detected:"<<no_of_deadlocks<<endl;
		//Start the reverse process and try to reach the start node now.
		cout<<"Printing wait message array"<<endl;
		for(int m = 0; m<msg_count.size(); m++) {
			cout<<msg_count.at(m)<<endl;
		}

		if(no_of_deadlocks >= 2 ) {
			cout<<"\n Detecting knot ....................................."<<endl;
			vector<vector<int> > wait_graph_copy(wait_graph);
			for (int col = no_of_process; col > 0; col--) {
				if (wait_graph.at(col-1).at(probe_pid) == 1) {
					cout << " S" << (probe_pid + 1) << " --> S" << (col) << "     (" << (probe_pid + 1) << "," << (probe_pid + 1) << "," << (col) << ")" <<" , \t"<< wait_msg[probe_pid]<<" , \t"<<msg_count[probe_pid]<<endl;
					reply_query(wait_graph_copy, probe_pid, (col-1));
				}
			}
		}

		cout<<"Number of knots detected:"<<no_of_knots<<endl;
		if(no_of_deadlocks == no_of_knots) {
			cout << "Equal number of Deadlock and Knot detected. \n All sent messages were received. \nHence the Chandy-Misra-Hass OR detected is validated." << endl;
		}
	} else {
		cout << "Deadlock detection not possible. No process running in the system" << endl;
	}
	return 0;
}

void disp_graph(vector<vector<int> > wait_graph) {
	int n = wait_graph.at(0).size();
	int m = wait_graph.size();

	//Top Column
	cout << "\t";
	for (int j = 0; j < m; j++) {
		cout << "S" << (j + 1) << "\t";
	}
	cout << endl;
	//Side column and values
	for (int i = 0; i<m; i++)
	{
		cout << "S" << (i + 1) << "\t";
		for (int j = 0; j<n; j++)
		{
			cout << wait_graph.at(i).at(j) << "\t";
			if (wait_graph.at(i).at(j) ==1)
			{
				msg_count[i] += 1;
				wait_msg[i] = true;
			}
		}
		cout << "\n";
	}
}

void engage_query(vector<vector<int> > graph, int init, int dest) {
	int end = no_of_process;
	for (int col = 0; col < end; col++)
	{
		if (graph[dest][col] == 1)
		{
			if (init == col)
			{
				cout << " S" << (dest + 1) << " --> S" << (col + 1) <<"     (" << (init + 1) << "," << (dest + 1) << "," << (col + 1) << ")" << " --------> DEADLOCK DETECTED HERE" << endl;
				deadlock_flag = 1;
				no_of_deadlocks += 1;
				break;
			}

			cout << " S" << (dest + 1) << " --> S" << (col + 1) << "     (" << (init + 1) << "," << (dest + 1) << "," << (col + 1) << ")" << " ,\t "<< wait_msg[dest]<<" ,\t "<<msg_count[dest]<<endl;
			engage_query(graph, init, col);
		}
	}
}

void reply_query(vector<vector<int> > graph, int init, int dest)
{
	int end = no_of_process;
	for (int col = (end-1); col >= 0 ; --col)
	{
		if (graph[col][dest] == 1)
		{
			if (msg_count[dest] != 0) { msg_count[dest] -= 1; }
			if (msg_count[dest] == 0) { wait_msg[dest] = false; }
			if (init == col)
			{
				cout << " S" << (dest + 1) << " --> S" << (col+1) <<"     (" << (init + 1) << "," << (dest + 1) << "," << (col+1) << ")" << " --------> KNOT DETECTED HERE" << endl;
				no_of_knots += 1;
				if(wait_msg[dest] == false && msg_count[dest] == 0)
				{
					break;
				}
			}
			if (msg_count[dest] == 0 && wait_msg[dest] == false) {
			       graph[col][dest] = 0;
			}

			cout << " S" << (dest + 1) << " --> S" << (col + 1) << "     (" << (init + 1) << "," << (dest + 1) << "," << (col+1) << ")" <<" , \t"<< wait_msg[dest]<<" , \t"<<msg_count[dest]<<endl;
			reply_query(graph, init, dest);
		}
	}
}
