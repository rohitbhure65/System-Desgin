interface Transport {
    void deliver();
}

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

abstract class Logistics {
    public void planDelivery() {
        Transport transport = createTransport();
        transport.deliver();
    }

    public abstract Transport createTransport();
}

class RoadLogistics extends Logistics {
    public Transport createTransport() {
        return new Truck();
    }
}

class SeaLogistics extends Logistics {
    public Transport createTransport() {
        return new Ship();
    }
}

public class factory_method {
    public static void main(String[] args) {
        Logistics logistics = new RoadLogistics();
        logistics.planDelivery();
    }
}
