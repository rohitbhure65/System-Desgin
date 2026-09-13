package state_structured;

class Context {
    private State state;

    public void setState(State state) {
        this.state = state;
    }

    public State getState() {
        return state;
    }
}
