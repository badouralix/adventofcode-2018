#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

struct SleepRecord
{
    int day, month, year;
    int hour, min;
    string message;
};

struct SleepPeriod
{
    uint minuteBegin, minuteEnd;
};

int main(int argc, char** argv) {
    string s = string(argv[1]);
    stringstream ss(s);
    string line;

    map<string, SleepRecord> Records = {};
    //unordered_map<int, 
    while (getline(ss,line)){
        SleepRecord sr;
        sscanf(line.c_str(), "[ %d - %d - %d %d : %d ]", &sr.year, &sr.month, &sr.day, &sr.hour, &sr.min);
        sr.message = line.substr(19);
        Records[line.substr(0, 19)] = sr; // automatically sorted because its a map
    }
    int currentGuard = -1;
    SleepPeriod currentNap;
    unordered_map<int, vector<SleepPeriod>> Naps = {};
    unordered_map<int, int> TotalNaps = {};
    for(auto it=Records.begin();it!=Records.end();it++){
        // Because they're sorted, we have Guard#ID ... then falls asleep then wakes up until another guard ID
        
        switch(it->second.message[0]){
            case('G'):{
                if(currentGuard!=-1){
                    if(Naps.find(currentGuard)==Naps.end()){
                        Naps[currentGuard] = vector<SleepPeriod>(1,currentNap);
                    }
                    else
                    {
                        Naps[currentGuard].push_back(currentNap);
                    }
                    TotalNaps[currentGuard]+=currentNap.minuteEnd - currentNap.minuteBegin;
                }
                string tmp = it->second.message.substr(7);
                currentGuard = stoi(tmp.substr(0, tmp.find('b')));
                break;
            }
            case('f'):{
                currentNap.minuteBegin = it->second.min;
                break;
            }
            case('w'):{
                int minuteEnd = it->second.min;
                currentNap.minuteEnd = minuteEnd;
                if(Naps.find(currentGuard)==Naps.end()){
                    Naps[currentGuard] = vector<SleepPeriod>(1,currentNap);
                }
                else
                {
                    Naps[currentGuard].push_back(currentNap);
                }
                TotalNaps[currentGuard]+=minuteEnd - currentNap.minuteBegin;;
            }
        }
    }
    int maxSleep = 0;
    int maxGuard = 0;
    for(auto it = TotalNaps.begin();it!=TotalNaps.end();++it){
        if(it->second > maxSleep){
            maxSleep = it->second;
            maxGuard = it->first;
        }
    }
    int BestMinute = 0;
    int MaxMinutes = 0;
    unordered_map<int, int> Minutes = {};
    for(auto it = Naps[maxGuard].begin();it!=Naps[maxGuard].end();++it){
        for(int i = it->minuteBegin;i<it->minuteEnd;i++){
            Minutes[i]++;
            if(Minutes[i]>MaxMinutes){
                MaxMinutes = Minutes[i];
                BestMinute = i;
            }
        }
    }
    cout << maxGuard*BestMinute << "\n";
    return 0;
}
