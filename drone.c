#include <stdio.h>
#include <math.h>

// 1. VERİLER
typedef struct {
    float x;
    float y;
} Point;

typedef struct {
    Point location;
    float battery;
} Drone;

typedef struct {
    Point location;
    int is_visited;
} Waypoint;

// 2. MESAFE HESAPLAMA 
float get_distance(Point *p1, Point *p2) {
    return sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));
}

// 3. GÜVENLİK KONTROLÜ 
// Drone ve Hedef adreslerinin pointer alarak maliyet hesabı
int check_safety(Drone *drone, Point *target, Point *home) {
    float to_target = get_distance(&(drone->location), target);
    float target_to_home = get_distance(target, home);
    
    // Toplam gereken pil 
    float total_needed = to_target + target_to_home;

    if (drone->battery >= total_needed) {
        return 1; 
    }
    return 0; 
}


int main() {
    
    Point home = {0.0, 0.0};
    Drone drone = {{0.0, 0.0}, 100.0}; // 
    
    Waypoint targets[3] = {
        {{10.0, 10.0}, 0},
        {{20.0, 30.0}, 0},
        {{50.0, 50.0}, 0}
    };

    printf("--- Gorev Basliyor ---\n");
    printf("Baslangic Pil Durumu: %%%.1f\n", drone.battery);

    for (int i = 0; i < 3; i++) {
        // Pointer aritmetiği kullanımı
        Waypoint *current_wp = (targets + i);

        if (check_safety(&drone, &(current_wp->location), &home)) {
            // Hedefe git
            float travel_dist = get_distance(&(drone.location), &(current_wp->location));
            drone.battery -= travel_dist;
            drone.location = current_wp->location;
            current_wp->is_visited = 1;
            
            printf("[GOREV] Hedef %d basariyla ziyaret edildi. Kalan Pil: %%%.1f\n", i + 1, drone.battery);
        } else {
            printf("[UYARI] Hedef %d icin enerji yetersiz! Guvenli donus baslatildi.\n", i + 1);
            break;
        }
    }

    // Eve Dönüş
    float return_dist = get_distance(&(drone.location), &home);
    drone.battery -= return_dist;
    drone.location = home;

    printf("--- Gorev Sonu ---\n");
    printf("Drone Eve Dondu. Final Pil: %%%.1f | Konum: (%.1f, %.1f)\n", drone.battery, drone.location.x, drone.location.y);

    return 0;
}