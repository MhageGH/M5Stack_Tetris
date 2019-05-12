#include <M5Stack.h> // M5STACK
#include "BGM.h"
#include "tetris_wav.h"

static void I2S_Task(void *)
{
  const int waveStartPos = 0x2C, transUnit = 512;
  unsigned long wavePos = waveStartPos;
  while (1)
  {
    delay(60); // less than allowance : (dma_buf_count*dma_buf_len-2*transUnit)/2/sample_rate = (32*64-2*512)/2/8000 = 64ms
    int n = (transUnit < sizeof(tetris_wav) - wavePos) ? transUnit : sizeof(tetris_wav) - wavePos;
    size_t bytes_written;
    i2s_write_expand((i2s_port_t)0, (const char *)(&tetris_wav[wavePos]), n, 8, 16, &bytes_written, portMAX_DELAY); // input unsigned 8bit data, I2S outputs unsigned 16bit data.
    wavePos = (wavePos < sizeof(tetris_wav)) ? wavePos + n : waveStartPos;
  }
}

void BGM_Start()
{
  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_DAC_BUILT_IN | I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = 8000,                          // not work when SAMPLE_RATE < 8000
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // not work when using 8bit
      .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT, // monoral. set right data only
                                                    // (need both data when using I2S_CHANNEL_FMT_ALL_RIGHT)
      .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S_MSB),
      .intr_alloc_flags = 0,
      .dma_buf_count = 32, // set data before all the buffers are empty
      .dma_buf_len = 64,
      .use_apll = false};

  i2s_driver_install((i2s_port_t)0, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)0, NULL);
  size_t bytes_written;
  xTaskCreatePinnedToCore(I2S_Task, "I2S_Task", 4096, NULL, 1, NULL, 0);
}

void BGM_Stop()
{
  i2s_stop((i2s_port_t)0);
}
