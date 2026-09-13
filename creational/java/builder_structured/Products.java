package builder_structured;

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
