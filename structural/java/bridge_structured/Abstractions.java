package bridge_structured;

class Remote {
    protected Device device;

    public Remote(Device device) {
        this.device = device;
    }

    public void togglePower() {
        device.turnOn();
    }
}
