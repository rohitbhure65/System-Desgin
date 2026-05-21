class AdvancedMediaPlayer {
  void playVlc(String fileName) {
    print('Playing vlc file: $fileName');
  }
  
  void playMp4(String fileName) {
    print('Playing mp4 file: $fileName');
  }
}

class StripePaymentSystem {
  void makeStripePayment(double amount) {
    print('Processing \$$amount via Stripe');
  }
}

class PayPalPaymentSystem {
  void sendPayPalRequest(double amount) {
    print('Processing \$$amount via PayPal');
  }
}
