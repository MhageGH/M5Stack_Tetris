#include "I2S.h"

void I2S_Init()
{
  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_DAC_BUILT_IN | I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = 8000,                          // SAMPLE_RATE 8000 未満は正常動作しない
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // 8bitは正常動作しない
      .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT, // モノラル。右のデータ書き込みだけで良い。
                                                    // I2S_CHANNEL_FMT_RIGHT_LEFT と I2S_CHANNEL_FMT_ALL_RIGHTは左右のデータ書き込みが必要
      .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S_MSB),
      .intr_alloc_flags = 0,
      .dma_buf_count = 16, // 次のデータ書き込みまでにバッファを使い切ってしまう場合は増やす
      .dma_buf_len = 64,
      .use_apll = false};
  i2s_driver_install((i2s_port_t)0, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)0, NULL);
}

void I2S_Write(char *data, int numData)
{
  i2s_write_bytes((i2s_port_t)0, (const char *)data, numData, portMAX_DELAY);
}

void I2S_Stop()
{
  i2s_stop((i2s_port_t)0);
}
