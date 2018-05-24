/* PQ */
template<typename T, typename priority_t>
class PriorityQueue
{
public:

    typedef pair<priority_t, T> PQElement;
    priority_queue<PQElement, std::vector<PQElement>,
    greater<PQElement>> elements;

    inline bool empty() const
    {
        return elements.empty();
    }

    inline void put(T item, priority_t priority)
    {
        elements.emplace(priority, item);
    }

    T get()
    {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
private:

};
