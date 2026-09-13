package singleton_structured;

public class Main {
    public static void main(String[] args) {
        Database db1 = Database.getInstance();
        Database db2 = Database.getInstance();
        System.out.println("Are db1 and db2 the same instance? " + (db1 == db2));
    }
}
