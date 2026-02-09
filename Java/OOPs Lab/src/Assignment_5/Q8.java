package Assignment_5;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class Repository<K,V>{
    private Map<K,V> repo;

    public Repository(){
        repo = new HashMap<>();
    }
    public void add(K key, V value){
        repo.put(key, value);
    }
    public void remove(K key){
        repo.remove(key);
    }
    public V find(K key){
        return repo.get(key);
    }
    public List<V> findAll(){
        return new ArrayList<V>(repo.values());
    }
}

public class Q8{
    public static void main(String[] args){
        System.out.println();
        Repository<Integer, String> repo = new Repository<>();

        // Add elements
        repo.add(1, "Apple");
        repo.add(2, "Banana");
        repo.add(3, "Cherry");

        // Find one element
        System.out.println("Find key 2: " + repo.find(2));

        // Update existing key
        repo.add(2, "Blueberry");
        System.out.println("After update, key 2: " + repo.find(2));

        // Find all elements
        System.out.println("All values:");
        for (String s : repo.findAll()) {
            System.out.println(s);
        }

        // Remove an element
        repo.remove(1);
        System.out.println("After removing key 1:");

        for (String s : repo.findAll()) {
            System.out.println(s);
        }
    }
}
