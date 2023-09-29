import java.io.File;

import javax.sound.sampled.*;

public class read_wave {

    private static int sample_size;
    private static int sample_rate;
    private static byte[] audioData;

    public static void readWavFile(String filePath) {
        try {
            // Open the audio file
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(new File(filePath));
            AudioFormat audioFormat = audioInputStream.getFormat();
            
            sample_size = audioFormat.getSampleSizeInBits() / 8;
            sample_rate = (int) audioFormat.getSampleRate();
            int frame_num = (int) audioInputStream.getFrameLength();
            int byte_num = frame_num * sample_size;

            audioData = new byte[byte_num];
            audioInputStream.read(audioData);

        } catch (Exception e) {
            e.printStackTrace();

        }
    }
}
