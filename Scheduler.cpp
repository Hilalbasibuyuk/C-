#include <iostream> // Konsola yazdırma işlemleri için
#include <queue> // Öncelik kuyruğu için
#include <chrono> // Zaman ölçüm fonksiyonları için
#include <thread> 
#include <vector>

using namespace std;

class Task {
    public:
        string name;
        int priority;
        int executionTime;

        Task(string n, int p, int e) : name(n), priority(p), executionTime(e) {}

        void execute() {
            cout << "[Executing] " << name << " (Priority: " << priority << ")\n";
            this_thread::sleep_for(chrono::milliseconds(executionTime));
            cout << "[Completed] " << name << "\n";
        }
};

// Öncelik bazlı karşılaştırma için lambda fonksiyonu
struct CompareTask {
    bool operator() (const Task &t1, const Task &t2) const {
        return t1.priority < t2.priority; // Önceliği yüksek olan önce çalıştırılır
    }
};

// Zamanlayıcı sınıfı
class Scheduler{
    private:
        priority_queue<Task, vector<Task>, CompareTask> taskQueue;
    public:
        void addTask(Task t) {
            taskQueue.push(t);
        }

        void run() {
            while (!taskQueue.empty()) {
                Task t = taskQueue.top();
                taskQueue.pop();
                t.execute();
            }
        }
};

int main() {
    Scheduler scheduler;

    scheduler.addTask(Task("Sensor Data Read", 2, 1000));
    scheduler.addTask(Task("Save Log File", 1, 500));
    scheduler.addTask(Task("Process Data", 3, 1500));

    // Görevleri çalıştır
    scheduler.run();
    
    return 0;
}
