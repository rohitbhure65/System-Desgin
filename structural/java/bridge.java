interface Device {
    void turnOn();
}

class TV implements Device {
    public void turnOn() {
        System.out.println("TV on");
    }
}

class Remote {
    protected Device device;

    public Remote(Device device) {
        this.device = device;
    }

    public void togglePower() {
        device.turnOn();
    }
}

public class bridge {
    public static void main(String[] args) {
        Remote remote = new Remote(new TV());
        remote.togglePower();
    }
}
