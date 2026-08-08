# STM32F4-Embedded-Software-Architecture
Integrated C-based peripheral driver framework including GPIO, ADC+DMA, Circular Buffer and Non-blocking UART for STM32F4"

# STM32F4 Embedded Peripheral Driver Framework

Bu proje; STM32F4 mikrodenetleyici mimarisi üzerinde modüler, yeniden kullanılabilir ve bloklamayan (non-blocking) sürücü katmanlarının (Driver Layers) tek bir çatı altında entegrasyonunu sunmaktadır.

## 🏛️ Sistem Mimarısı ve Modüller

- **GPIO & Software Debounce Driver:** Buton sıçramalarını engelleyen non-blocking debounce algoritması ve modüler LED/Giriş yönetimi.
- **ADC + DMA & Kalibrasyon Sürücüsü:** Dahili $V_{DDA}$ kalibrasyonu (`VREFINT`), chip içi sıcaklık sensörü okuması ve potansiyometre verilerinin ortalama filtreleme (averaging) ile işlenmesi.
- **Buffered UART & Circular Buffer:** Kesme (Interrupt) tabanlı, $512$ byte FIFO dairesel tampon bellek destekli, bloklamayan `UARTx_Printf` ve satır ayrıştırma (`ReadLine`) altyapısı.

## 📁 Dosya Yapısı

- `io_driver.c / .h` : GPIO ve Debounce sürücüsü
- `adc_driver.c / .h` : ADC, DMA ve Kalibrasyon sürücüsü
- `Circuler_Buffer.c / .h` : FIFO Dairesel Tampon yapısı
- `UART_ex.c / .h` : Kesme tabanlı UART ve Printf yönlendirmesi
