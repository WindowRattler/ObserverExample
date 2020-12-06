//BenjaminKramer
//12-6-2020

//This is an illustration of an Observer Design Pattern
//Using a baseball game data collection
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

// base class used by classes that do OBSERVING (i.e., a "display")!
class Observer {
  public:
    virtual void update(int runs, int hits, int terrain, int weather, int timeOfDay, float win_average)=0;
};

class Subject {
  public:
    virtual void registerObserver(Observer* o)=0;
    virtual void unregisterObserver(Observer* o)=0;
    virtual void notifyObservers()=0;
};

class SportsData:public Subject {
  private:
    int runs;
    int hits;
    int terrain;
    int weather;
    int timeOfDay;
    float win_average;
    vector<Observer*> observerList;

    void notifyObservers() {
      for (int i = 0; i < observerList.size(); i++ ) {
        if (observerList.at(i) != nullptr) {
          observerList.at(i)->update(runs,hits,terrain,weather,timeOfDay,win_average);
        }
      }
    }
    
    int getLatestRuns() {
      int value = rand() % 10;
      return (value > hits) ? hits : value;
    }

    int getLatestHits() {
      return (rand() % 10);
    }

    int getFieldTerrain() {
      return (rand() % 10);
    }

    int getLatestWeather() {
      return (rand() % 10);
    }

    int getLatestTimeOfDay() {
      return (rand() % 10);
    }

    float getLatestWinAverage() {
      return floorf(((float) rand() / (RAND_MAX)) * 1000) / 1000;
    }

  public:
    SportsData() {
        srand(time(0));  // Initialize random number generator.
    }

    void registerObserver(Observer* o) {
      observerList.push_back(o);
    }

    void unregisterObserver(Observer* o) {
      for (int i = 0; i < observerList.size(); i++ ) {
        if (observerList.at(i) == o) {
          observerList.erase(observerList.begin()+i);
        }
      }
    }

    // This method is used update data and displays
    void dataChanged() {
      
      //get latest data
      hits = getLatestHits();
      runs = getLatestRuns();
      terrain = getFieldTerrain();
      weather = getLatestWeather();
      timeOfDay = getLatestTimeOfDay();
      win_average = getLatestWinAverage();

      notifyObservers();
    }

};

class CalcScoreDisplay: public Observer {
  private:
    float runRate;

  public:
    void update(int runs, int hits, 
                int terrain, int weather, 
                int timeOfDay, float win_average) {
                         
      runRate = (hits > 0)
       ? (ceilf(((float)runs /  (float)hits)*1000)/1000) 
       : 0;
      display();
    }

    void display() {
      cout << "\nRuns Per Hit: \n";
      cout << runRate << "\n";
    }
};

class CurrentScoreDisplay: public Observer {
  private:
    int runs, hits, terrain, weather, timeOfDay;
    float win_average;

  public:
    void update(int new_runs, int new_hits,
                       int new_terrain,
                       int new_weather,
                       int new_timeOfDay,
                       float new_win_average) {
      runs = new_runs;
      hits = new_hits;
      terrain = new_terrain;
      weather = new_weather;
      timeOfDay = new_timeOfDay;
      win_average = new_win_average;
      display();
    }

    void display() {
      cout << "\nCurrent Score Display:\n";
      cout << "Runs: " << runs;
      cout << "\nHits:" << hits;
      cout << "\nTerrain:" << terrain;
      cout << "\nWeather:" << weather;
      cout << "\nTime of Day:" << timeOfDay;
      cout << "\nWin Average: " << win_average << "\n";
    }
};

int main() {
  cout << "Key for Terrain:" << endl;
  cout << "From 0-4 = Turf, From 5-7 = Dirt, From 8-10 = Grass" << endl;
  cout << "Key for Weather:" << endl;
  cout << "From 0-4 = Clear, From 5-7 = Overcast, From 8-10 = Rainy" << endl;
  cout << "Key for Time of Day:" << endl;
  cout << "From 0-2 = Dawn, From 3-5 = Day, \nFrom 6-8  = Dusk, From 9-10 = Night" << endl;
  // create objects for display
  CalcScoreDisplay calcScoreDisplay = CalcScoreDisplay();
  CurrentScoreDisplay currentScoreDisplay = CurrentScoreDisplay();

  SportsData sportsData = SportsData();

  // register display elements
  sportsData.registerObserver(&calcScoreDisplay);
  sportsData.registerObserver(&currentScoreDisplay);

  sportsData.dataChanged();

  //remove an observer and re-run dataChanged()
  sportsData.unregisterObserver(&currentScoreDisplay);
  sportsData.dataChanged();
} 
