export class AdvancedMediaPlayer {
  playVlc(fileName: string): void { console.log(`Playing vlc file: ${fileName}`); }
  playMp4(fileName: string): void { console.log(`Playing mp4 file: ${fileName}`); }
}

export class StripePaymentSystem {
  makeStripePayment(amount: number): void { console.log(`Processing $${amount} via Stripe`); }
}

export class PayPalPaymentSystem {
  sendPayPalRequest(amount: number): void { console.log(`Processing $${amount} via PayPal`); }
}
