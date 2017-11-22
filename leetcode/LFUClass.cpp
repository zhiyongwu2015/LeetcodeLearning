class LFUCache {
public:
    LFUCache(int capacity) {
        CacheSize = capacity;
    }
    
    int get(int key) {
        if (!m.find(key)) return -1;//no key 
        freq[m[key].second].erase(position[key]);//重置value
        ++m[key].second;//访问记录
        freq[m[key].second].push_back(key);
        position[key] = --freq[m[key].second].end();
        if (freq[minFreq].size() == 0) ++minFreq;
        return m[key].first;
    }
    
    void set(int key, int value) {
        if (CacheSize <= 0) return;
        if (get(key) != -1) {
            m[key].first = value;
            return;
        }
        //Catch 满时，删除最少访问的数据。
        if (m.size() >= CacheSize) {
            m.erase(freq[minFreq].front());
            position.erase(freq[minFreq].front());
            freq[minFreq].pop_front();
        }
        m[key] = {value, 1};
        freq[1].push_back(key);
        position[key] = --freq[1].end();
        minFreq = 1;
    }

private:
    int CacheSize, minFreq;//容量和当前最小访问频率
    unordered_map<int, pair<int, int>> m;//哈希实现当前数据和访问频率的对应关系
    unordered_map<int, list<int>> freq;//相同频率key,放入同一个list链表中，用freq存其的对应关系
    unordered_map<int, list<int>::iterator> position;//建立key和freq中key的位置对应关系
};