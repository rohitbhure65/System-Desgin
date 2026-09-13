package factory_method_structured;

class Truck implements Transport {
    public void deliver() {
        System.out.println("Deliver by land in a box.");
    }
}

class Ship implements Transport {
    public void deliver() {
        System.out.println("Deliver by sea in a container.");
    }
}
