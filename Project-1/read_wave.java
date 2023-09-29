import java.io.File;

import javax.sound.sampled.*;

public class read_wave {

    private static int bytes_per_sample;
    private static int sample_rate;
    private static byte[] data_c1;
    private static byte[] data_c2;

    public static void readWavFile(String filePath) {
        try {
            // Open the audio file
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(new File(filePath));
            AudioFormat audioFormat = audioInputStream.getFormat();
            
            bytes_per_sample = audioFormat.getSampleSizeInBits() / 8;
            sample_rate = (int) audioFormat.getSampleRate();
            int frame_num = (int) audioInputStream.getFrameLength();
            int byte_num_per_channel = frame_num * bytes_per_sample;

            data_c1 = new byte[byte_num_per_channel];
            data_c2 = new byte[byte_num_per_channel];
            byte[] data = new byte[byte_num_per_channel*2];
            audioInputStream.read(data);

            for (int i = 0; i < byte_num_per_channel; i++) {
                data_c1[i] = data[i * 2];
                data_c2[i] = data[i * 2 + 1];
            }

        } catch (Exception e) {
            e.printStackTrace();

        }
    }
}
