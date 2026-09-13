package builder_structured;

public class Main {
    public static void main(String[] args) {
        Director director = new Director();
        CarBuilder builder = new CarBuilder();
        director.constructSportsCar(builder);
        Car car = builder.getProduct();
        car.show();
    }
}
