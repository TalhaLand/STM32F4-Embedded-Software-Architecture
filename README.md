# STM32F4-Embedded-Software-Architecture
Integrated C-based peripheral driver framework including GPIO, ADC+DMA, Circular Buffer and Non-blocking UART for STM32F4"

## STM32F4 Embedded Peripheral Driver Framework

Bu proje; gömülü sistemler eğitimi ve pratiklerim kapsamında STM32F4 konfigürasyonları için şu ana kadar modüler olarak geliştirdiğim tüm çevre birimi (peripheral) sürücülerinin tek bir çatı altında birleştirilmiş halidir.

Projenin temel amacı; donanım katmanından soyutlanmış, tekrar kullanılabilir (reusable), bloklamayan (non-blocking) ve bellek dostu bir sürücü mimarisi oluşturmaktır.

---

## 🛠️ Entegre Edilen Sürücüler ve Özellikleri

### 1. GPIO Driver & Software Debounce (`io_driver`)
- Giriş ve çıkış pinleri için `struct` tabanlı modüler veri yapısı.
- `HAL_GetTick()` kullanılarak oluşturulmuş, işlemciyi bloklamayan yazılımsal buton debounce (sıçrama önleme) algoritması.

### 2. ADC + DMA & Hardware Calibration (`adc_driver`)
- İşlemci yükünü sıfıra indiren DMA destekli çok kanallı ADC okuması.
- Dahili `VREFINT` kanalı kullanılarak yapılan anlık $V_{DDA}$ gerilimi kalibrasyonu.
- Dahili sıcaklık sensörü hesabı ve potansiyometre okumaları için 64 örneklemeli hareketli ortalama (averaging) filtresi.
- Volt değerini %0 - %100 aralığına dönüştüren özel haritalama (mapping) fonksiyonu.

### 3. Circular Buffer & Interrupt-Driven UART (`UART_ex` & `Circuler_Buffer`)
- $512$ byte boyutunda FIFO (First-In, First-Out) mantığıyla çalışan dairesel tampon bellek.
- Kesme (Interrupt) tabanlı, arka planda çalışan ve iletim sırasında ana döngüyü (main loop) bekletmeyen UART mimarisi.
- `va_list` ve `vsnprintf` kullanılarak özelleştirilmiş hızlı `UARTx_Printf` fonksiyonu.
- `\r\n` karakterlerini algılayan komut/satır okuma (`UARTx_ReadLine`) yapısı.

---

## 📁 Proje Klasör Yapısı

```text
├── Inc/
│   ├── io_driver.h         # GPIO ve Debounce başlık dosyası
│   ├── adc_driver.h        # ADC, DMA ve Kalibrasyon başlık dosyası
│   ├── Circuler_Buffer.h   # Dairesel tampon bellek veri yapıları
│   └── UART_ex.h           # Kesme tabanlı UART ve Printf prototipleri
├── Src/
│   ├── io_driver.c         # GPIO sürücü mantığı
│   ├── adc_driver.c        # ADC ve dönüştürme fonksiyonları
│   ├── Circuler_Buffer.c   # Tampon ekleme/çıkarma (Enqueue/Dequeue)
│   ├── UART_ex.c           # Printf ve UART sürücüsü
│   ├── stm32f4xx_it.c      # ISR (Interrupt Service Routine) işleyicileri
│   └── main.c              # Sürücülerin entegre çalıştığı ana uygulama döngüsü
