#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool backtrack(const AvailabilityMatrix& avail,
            size_t dailyNeed,
            size_t maxShifts,
            DailySchedule& sched,
            vector<size_t>& shiftsWorked,
            size_t currDay,
            size_t currWorkers);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();

    sched.resize(numDays, vector<Worker_T>(dailyNeed, -1)); // -1 as placeholder
    vector<size_t> numShiftsWorked(numWorkers, 0);

    return backtrack(avail, dailyNeed, maxShifts, sched, numShiftsWorked, 0, 0);
}


bool backtrack(const AvailabilityMatrix& avail,
            size_t dailyNeed,
            size_t maxShifts,
            DailySchedule& sched,
            vector<size_t>& shiftsWorked,
            size_t currDay,
            size_t currWorkers) {
    
    if (currDay == sched.size()) {
        return true; // All days filled
    }

    // Move to next day if current one is filled
    if (currWorkers == dailyNeed) {
        return backtrack(avail, dailyNeed, maxShifts, sched, shiftsWorked, currDay + 1, 0);
    }

    size_t numWorkers = avail[0].size();
    for (size_t worker = 0; worker < numWorkers; ++worker) {
        if (avail[currDay][worker] &&
            shiftsWorked[worker] < maxShifts &&
            find(sched[currDay].begin(), sched[currDay].end(), worker) == sched[currDay].end()) {

            sched[currDay][currWorkers] = worker;
            shiftsWorked[worker]++;

            if (backtrack(avail, dailyNeed, maxShifts, sched, shiftsWorked, currDay, currWorkers + 1)) {
                return true;
            }

            // Backtrack
            shiftsWorked[worker]--;
            sched[currDay][currWorkers] = -1; // Optional: to help debugging
        }
    }

    return false; // No valid assignment for this slot
}

