#include<iostream>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;



//// Function to find the system is in safe state or not
bool isSafe(int n,int m, vector<int> &avail, vector< vector<int> > &Max, vector< vector<int> > &Alloc, 
    vector< vector<int> > &Need, vector<int> &safeSeq)
{
    int i, j, k;
    bool* finish = new bool[n];
    int* work = new int[m];

    for (i = 0; i < n; i++) {
        finish[i] = false;
    }

    for (i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < n)
    {

        bool found = false;
        for (i = 0; i < n; i++)
        {

            if (finish[i] == 0)
            {

                for (j = 0; j < m; j++)
                    if (Need[i][j] > work[j])
                        break;

                if (j == m)
                {

                    for (k = 0; k < m; k++)
                        work[k] += Alloc[i][k];

                    safeSeq[count++] = i;

                    finish[i] = 1;

                    found = true;
                }
            }
        }
        if (found == false)
        {
            return false;
        }
    }

    delete[] finish;
    delete[] work;
    
    return true;
}

bool Res_req(int n, int m, int pid, vector<int> &avail, vector< vector<int> > &Max, vector< vector<int> > &Alloc,
    vector< vector<int> > &Need, vector<int> &Req, vector<int> &safeSeq) {

    int i, j, k;
    bool grant;
    for (i = 0; i < m; i++) {
        if (Req[i] > Need[pid][i]) {
            cout << "Error occured , The Request Cannot be granted" << endl;
            return false;
        }
        else {
            if (Req[i] > avail[i]) {
                cout << "The Request Cannot be granted , the process 'P"<<pid<<" will wait the  resources" << endl;
                return false;
            }
        }
    }

    for (i = 0; i < m; i++) {
        if (Req[i] <= avail[i]) {
            avail[i] = avail[i] - Req[i];
            Alloc[pid][i] = Alloc[pid][i] + Req[i];
            Need[pid][i] = Need[pid][i] - Req[i];
        }
    }

    grant = isSafe(n, m, avail, Max, Alloc, Need, safeSeq);

    if (grant == true) {
        cout << "\n Yes , Request can be granted with safe state ,Safe state <";
        cout << "P" << pid << "req"<<",";
        for (i = 0; i < n; i++) {
            cout << "P" << safeSeq[i];
            if (i != (n - 1)) {
                cout << ",";
            }
        }
        cout << ">" << endl;
        for (i = 0; i < m; i++) {
             avail[i] = avail[i] + Req[i];
             Alloc[pid][i] = Alloc[pid][i] - Req[i];
             Need[pid][i] = Need[pid][i] + Req[i];
        }
        return true;
    }
    else if (grant == false) {
        cout << "No" << endl;
        cout << "The Request Cannot be granted , the system with unsafe state " << endl;
        for (i = 0; i < m; i++) {
            avail[i] = avail[i] + Req[i];
            Alloc[pid][i] = Alloc[pid][i] - Req[i];
            Need[pid][i] = Need[pid][i] + Req[i];
        }
        return false;
    }

}

int main() {
    
        int n = 0, m = 0; // n = no.of process , m = no.of resources
        int i, j, k;
        int input = 0;
        char c1,c2, again;
    do{
        input = 0, n = 0, m = 0;
        cout << "Please enter number of Process: " << endl;
        cin >> n;
        cout << "Please enter number of Resources: " << endl;
        cin >> m;

        vector<vector<int>> Alloc(n, vector<int>(m, 0));
        vector<vector<int>> Max(n, vector<int>(m, 0));
        vector<vector<int>> Need(n, vector<int>(m, 0));
        vector<int> Avail(m, 0);

        vector<int> safeSeq(n, 0);// To store safe sequence

        for (i = 0; i < n; i++) {
            safeSeq[i] = 0;
        }

        cout << "Please enter Allocation table in this form:"
            " 1 2 3 4 5 (Resources numbers should be seperated by spaces) and (press enter after each row at each new process)"
            "(like Matrices but without brackets):" << endl;
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                cin >> input;
                Alloc[i][j] = input;
            }
        }

        cout << "Please enter Max table in this form:"
            " 1 2 3 4 5 (Resources numbers should be seperated by spaces) and (press enter after each row at each new process)"
            "(like Matrices but without brackets):" << endl;
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                cin >> input;
                Max[i][j] = input;
            }
        }

        cout << "Please enter Available row in this form 1 2 3 4 5 (Resources numbers should be seperated by spaces): " << endl;
        for (i = 0; i < m; i++) {
            cin >> input;
            Avail[i] = input;
        }

        // calculating Need Matrix 
        cout << "\n Need Matrix: \n" << endl;
        cout << "    ";
        for (i = 0; i < m; i++)
        {
            cout << "R" << i << "  ";
        }
        cout << endl;
        for (i = 0; i < n; i++) {
            cout << 'P' << i << "  ";
            for (j = 0; j < m; j++) {
                Need[i][j] = (Max[i][j]) - (Alloc[i][j]);
                cout << Need[i][j] << "   ";
            }
            cout << "\n";
        }

        bool flag1 =false,flag2=false;
        int pid;
        vector<int> Req(m, 0);
        
        do {
            cout << "\nDo you want to know the safe state ? (Y/N) \n";
            cin >> c1;
        } while (c1 != 'Y' && c1 != 'y' && c1 != 'N' && c1 != 'n');

        if (c1 == 'Y' || c1 == 'y') {
            flag1 = isSafe(n, m, Avail, Max, Alloc, Need, safeSeq);
            if (flag1 == false) {
                cout << "No" << endl;
            }
            else if (flag1 == true) {
                cout << "\n Yes , Safe state <";
                for (i = 0; i < n; i++) {
                    cout << "P" << safeSeq[i];
                    if (i != (n - 1)) {
                        cout << ",";
                    }
                }
                cout << ">" << endl;
            }
        }
        if (flag1 == false && (c1 == 'Y' || c1 == 'y')) {
            cout << "there is no immediate requests because the system with unsafe state " << endl;
            cout << " \nEnter 0: to restert the program , Q: to end the program " << endl;
            cin >> again;
            if (again == 'Q' || again == 'q') {
                cout << "\nThank You" << endl;
                exit(0);
            }
      }
        
        do {
            cout << "\nDo you want immediate requests ? (Y/N) \n";
            cin >> c2;
        } while (c2 != 'Y' && c2 != 'y' && c2 != 'N' && c2 != 'n');

        if (c2 == 'Y' || c2 == 'y') {
            do {
                do {
                    cout << "Please enter the pid of the process that demand the request from (0 to n-1) ,where n is no. of process  " << endl;
                    cin >> pid;
                } while ((pid >= n) || (pid < 0));

                cout << "Please enter Requested row in this form 1 2 3 4 5 (Resources numbers should be seperated by spaces):" << endl;
                for (i = 0; i < m; i++) {
                    cin >> input;
                    Req[i] = input;
                }
                flag2 = Res_req(n, m, pid, Avail, Max, Alloc, Need, Req, safeSeq);
                cout << " \nEnter 1 : to another request , 0: to restert the program , Q: to end the program " << endl;
                cin >> again;
            } while (again == '1');
        }

        else if (c2 == 'N' || c2 == 'n') {
            cout << "Thank You" << endl;
            cout << " \nEnter 0: to restert the program , Q: to end the program "<<endl;
            cin >> again;
        }
        if (again == 'Q' || again == 'q') {
            cout << "\nThank You" << endl;
            exit(0);
        }

    }while (again == '0');

	return 0;
}