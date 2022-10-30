#include<bits/stdc++.h>

using namespace std;

void print_help();

int main(int argc, char ** argv) {

    if (argc < 2) {
        print_help();
    } 

    else {
        map < string, int > m;
        m["add"] = 1;
        m["ls"] = 2;
        m["del"] = 3;
        m["done"] = 4;
        m["report"] = 5;

        fstream fout;
        multimap < int, string > taskXprior;
        fout.open("task.txt", ios:: in );
        if (fout.is_open()) {
            string line;
            while (getline(fout, line)) {
                auto priority = stoi(line.substr(0, line.find(' ')));
                auto taskname = line.substr(line.find(' ') + 1, line.length());
                taskXprior.insert({
                    priority,
                    taskname
                });

            }
            fout.close();
            fout.open("task.txt", ios::out); {
                for (auto it: taskXprior) {
                    fout << it.first << " " << it.second << endl;
                }
                fout.close();
            }

        }
        int command = m[argv[1]];

        switch (command) {
        case 1:
        {
           try{
             auto priority = stoi(argv[2]);
            string taskname = argv[3];
            taskXprior.insert({priority, taskname});
            fout.open("task.txt", ios::out);
            if (fout.is_open()) {
                for (auto it: taskXprior) {
                    // cout<<it.first<<" "<<it.second<<endl;
                    fout << it.first << " " << it.second << endl;
                }
                fout.close();
            }
            cout << "Added task: \"" << taskname << "\" with priority " << priority << endl;
           }
           catch(...){
             cout<<"Error: Missing tasks string. Nothing added!"<<endl;
           }

        }
    
            break;
        case 2: {


            int pendingt = 0;
            for (auto it: taskXprior) {
                pendingt++;
            }
            if(pendingt<1){
                 cout<<"There are no pending tasks!"<<endl;
            }
        else{

        fout.open("task.txt", ios:: in );
            if (fout.is_open()) {
                string line;
                int count = 1;
                while (getline(fout, line)) {
                    auto priority = stoi(line.substr(0, line.find(' ')));
                    auto taskname = line.substr(line.find(' ') + 1, line.length());
                    cout << count << ". " << taskname << " [" << priority << "]" << endl;
                    count++;
                }
                fout.close();
            } 
        }


        }
        break;

        case 3: {

            int pendingt = 0, completedt = 0;
            auto index = stoi(argv[2]);
            for (auto it: taskXprior) {
                pendingt++;
            }
            fout.open("completed.txt", ios:: in );
            if (fout.is_open()) {
                string s;
                while (getline(fout, s)) {
                    completedt++;
                }
                fout.close();
            }
            // cout<<pendingt<<" "<<completedt;

            if (pendingt < index) {
                cout << "Error: item with index " << index << " does not exist. Nothing deleted." << endl;
            } else {
                auto it = taskXprior.begin();
                for (int i = 0; i < index - 1; i++) {
                    it++;
                }
                taskXprior.erase(it);
                fout.open("task.txt", ios::out); {
                    for (auto it: taskXprior) {
                        fout << it.first << " " << it.second << endl;
                    }
                    fout.close();
                }
                cout << "Deleted task #" << index << endl;
            }

        }
        break;

        case 4: {
            int pendingt = 0, completedt = 0;
            auto index = stoi(argv[2]);
            for (auto it: taskXprior) {
                pendingt++;
            }
            fout.open("completed.txt", ios:: in );
            if (fout.is_open()) {
                string s;
                while (getline(fout, s)) {
                    completedt++;
                }
                fout.close();
            }

            if (pendingt < index) {
                cout << "Error: no incomplete item with index " << index << " exists." << endl;
            } else {
                int num;
                string str; {
                    auto it = taskXprior.begin();
                    for (int i = 0; i < index - 1; i++) {
                        it++;
                    }

                    num = it -> first;
                    str = it -> second;
                    taskXprior.erase(it);
                    fout.open("task.txt", ios::out); {
                        for (auto it: taskXprior) {
                            fout << it.first << " " << it.second << endl;
                        }
                        fout.close();
                    }
                }
                fout.open("completed.txt", ios::app);
                if (fout.is_open()) {

                    fout << num << " " << str << endl;

                    fout.close();
                }
                cout << "Marked item as done." << endl;
            }

            // completed.insert({num, str});

        }
        break;
        case 5: {
            int pendingt = 0, completedt = 0;
            for (auto it: taskXprior) {
                pendingt++;
            }
            fout.open("completed.txt", ios:: in );
            if (fout.is_open()) {
                string s;
                while (getline(fout, s)) {
                    completedt++;
                }
                fout.close();
            }

            cout << "Pending : " << pendingt << endl;

            fout.open("task.txt", ios:: in );
            if (fout.is_open()) {
                string line;
                int count = 1;
                while (getline(fout, line)) {
                    auto priority = stoi(line.substr(0, line.find(' ')));
                    auto taskname = line.substr(line.find(' ') + 1, line.length());
                    cout << count << ". " << taskname << " [" << priority << "]" << endl;
                    count++;
                }
                fout.close();
            }

            cout << endl;
            cout << "Completed : " << completedt << endl;

            fout.open("completed.txt", ios:: in );
            if (fout.is_open()) {
                string line;
                int count = 1;
                while (getline(fout, line)) {
                    auto priority = stoi(line.substr(0, line.find(' ')));
                    auto taskname = line.substr(line.find(' ') + 1, line.length());
                    cout << count << ". " << taskname << endl;
                    count++;
                }
                fout.close();
            }

        }
        break;

        default:
            print_help();
            break;
        }

    }
}
    void print_help() {
        cout << "Usage :-\n";
        cout << "$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list\n";
        cout << "$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order\n";
        cout << "$ ./task del INDEX            # Delete the incomplete item with the given index\n";
        cout << "$ ./task done INDEX           # Mark the incomplete item with the given index as complete\n";
        cout << "$ ./task help                 # Show usage\n";
        cout << "$ ./task report               # Statistics\n";
    }
