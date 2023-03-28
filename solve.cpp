#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include<bits/stdc++.h>
using namespace std;

class Drone {
public:
    int id;
    int x;
    int y;
    float speed;
    int time;
    Drone(int id, int x, int y, float speed, int time) {
        this->id = id;
        this->x = x;
        this->y = y;
        this->speed = speed;
        this->time = time;
    }
};

class Movement {
public:
    int drone_id;
    int dx;
    int dy;
    Movement(int drone_id, int dx, int dy) {
        this->drone_id = drone_id;
        this->dx = dx;
        this->dy = dy;
    }
};

float distance(int x1, int y1, int x2, int y2) {
    return pow((pow((x2 - x1), 2) + pow((y2 - y1), 2)), 0.5);
}

void get_paths_helper(vector<Drone> &drones,vector<vector<int>> &path, vector<vector<vector<int>>> &paths) {
    if (path.size() == drones.size()) {
        paths.push_back(path);
        return;
    }
    int last_x = path[path.size() - 1][1];
    int last_y = path[path.size() - 1][2];
    for (int i = 0; i < drones.size(); i++) {
        bool in_path = false;
        for (int j = 0; j < path.size(); j++) {
            if (i == path[j][0]) {
                in_path = true;
            }
        }
        if (!in_path) {
            Drone drone = drones[i];
            float d = distance(last_x, last_y, drone.x, drone.y);
            if (d / drone.speed <= drone.time) {
                vector<int> point = {i, drone.x, drone.y};
                path.push_back(point);
                get_paths_helper(drones, path, paths);
                path.pop_back();
            }
        }
    }
}

vector<vector<vector<int>>> get_paths(vector<Drone> &drones) {
    vector<vector<vector<int>>> paths;
    for (int i = 0; i < drones.size(); i++) {
        std::vector<std::vector<int>> path;
        std::vector<int> point = {i, drones[i].x, drones[i].y};
        path.push_back(point);
        get_paths_helper(drones, path, paths);
    }
    return paths;
}

void simulate(vector<Drone> drones, vector<vector<vector<int>>> paths) {
    for (int i = 0; i < paths[0].size(); i++) {
        map<int,pair<int, int>> locations;
        for (Drone drone : drones) {
            locations[drone.id] = make_pair(drone.x, drone.y);
        }
        for (int j = 0; j < drones.size(); j++) {
            Drone drone = drones[j];
            Movement move(paths[j][i][0],paths[j][i][1],paths[j][i][2]);
            drone.x = move.dx;
            drone.y = move.dy;
            std::cout << "Drone " << drone.id << ": " << locations[drone.id].first << ", " << locations[drone.id].second << " -> (" << drone.x << ", " << drone.y << ")" <<endl;
        }
        for (int j = 0; j < drones.size(); j++) {
            Drone drone1 = drones[j];
            for (int k = j + 1; k < drones.size(); k++) {
                Drone drone2 = drones[k];
                if (drone1.x == drone2.x and drone1.y == drone2.y)
                    cout<<"Collision between drone"<< drone1.id<<" and drone "<<drone2.id;
            }
        }
        sleep(1);
    }
}
int main()
{
   int n;
   cin>>n;
   vector<Drone> drones(n)
   
   for(int i=0;i<n;i++)
   {
    int x1,y1,x12,y12,t1;
    Drone(x1,y1,x12,y12,t1);
   }
   vector<vector<vector<int>>> paths = get_paths(drones);
   for(int i=0;i<paths.size();i++){
       cout<<"Drone "<<i<<":"<<endl;
       for(auto point : paths[i])
           cout<<point[1]<<" "<<point[2]<<endl;
   }
   return 0;
}
