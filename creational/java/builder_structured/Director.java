package builder_structured;

class Director {
    public void constructSportsCar(Builder builder) {
        builder.reset();
        builder.setSeats("2 seats");
        builder.setEngine("V8 engine");
    }
}
