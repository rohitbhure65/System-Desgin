class Car {
    private String seats;
    private String engine;

    public void setSeats(String seats) {
        this.seats = seats;
    }

    public void setEngine(String engine) {
        this.engine = engine;
    }

    public void show() {
        System.out.println("Car with " + seats + " and " + engine);
    }
}

interface Builder {
    void reset();

    void setSeats(String seats);

    void setEngine(String engine);
}

class CarBuilder implements Builder {
    private Car car;

    public CarBuilder() {
        this.reset();
    }

    public void reset() {
        this.car = new Car();
    }

    public void setSeats(String seats) {
        this.car.setSeats(seats);
    }

    public void setEngine(String engine) {
        this.car.setEngine(engine);
    }

    public Car getProduct() {
        return this.car;
    }
}

class Director {
    public void constructSportsCar(Builder builder) {
        builder.reset();
        builder.setSeats("2 seats");
        builder.setEngine("V8 engine");
    }
}

public class builder {
    public static void main(String[] args) {
        Director director = new Director();
        CarBuilder builder = new CarBuilder();
        director.constructSportsCar(builder);
        Car car = builder.getProduct();
        car.show();
    }
}
