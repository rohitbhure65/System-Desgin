package builder_structured;

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
