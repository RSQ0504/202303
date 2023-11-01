import java.awt.*;
import java.io.File;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.HashMap;
import java.util.Map;

import javax.sound.sampled.*;
import javax.swing.*;

public class read_wave  extends JPanel {

    private static int bytes_per_sample;
    private static int sample_rate;
    private static byte[] data_c1;
    private static byte[] data_c2;
    private static byte[] total_data;
    private static AudioFormat audioFormat;


    public read_wave(String filePath) {
        try {
            // Open the audio file
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(new File(filePath));
            audioFormat = audioInputStream.getFormat();
            
            bytes_per_sample = audioFormat.getSampleSizeInBits() / 8;
            sample_rate = (int) audioFormat.getSampleRate();
            int frame_num = (int) audioInputStream.getFrameLength();
            int byte_num_per_channel = frame_num * bytes_per_sample;

            data_c1 = new byte[byte_num_per_channel];
            data_c2 = new byte[byte_num_per_channel];
            total_data = new byte[byte_num_per_channel*2];
            audioInputStream.read(total_data);

            for (int i = 0; i < byte_num_per_channel; i+=bytes_per_sample) {
                for(int j = 0; j<bytes_per_sample;j++){
                    data_c1[i+j] = total_data[i * 2 + j];
                    data_c2[i+j] = total_data[i * 2 + bytes_per_sample + j];
                }
            }

        } catch (Exception e) {
            e.printStackTrace();

        }
    }

    public void draw(){
        setLayout(new BorderLayout());
        repaint(); 
    }

    private static Map<Integer, Integer> calculate_freq(){
        Map<Integer, Integer> table = new HashMap<>();
        int sample_num = data_c1.length / bytes_per_sample;
        int c1_v1,c1_v2,c2_v1,c2_v2;
        for (int i = 0; i < sample_num - 1; i++) {
            if(audioFormat.isBigEndian()){
                c1_v1 = (int) (ByteBuffer.wrap(data_c1, i * bytes_per_sample, bytes_per_sample).order(ByteOrder.BIG_ENDIAN).getShort());
                c1_v2 = (int) (ByteBuffer.wrap(data_c1, (i + 1) * bytes_per_sample, bytes_per_sample).order(ByteOrder.BIG_ENDIAN).getShort());
                c2_v1 = (int) (ByteBuffer.wrap(data_c2, i * bytes_per_sample, bytes_per_sample).order(ByteOrder.BIG_ENDIAN).getShort());
                c2_v2 = (int) (ByteBuffer.wrap(data_c2, (i + 1) * bytes_per_sample, bytes_per_sample).order(ByteOrder.BIG_ENDIAN).getShort());
            }else{
                c1_v1 = (int) (ByteBuffer.wrap(data_c1, i * bytes_per_sample, bytes_per_sample).order(ByteOrder.LITTLE_ENDIAN).getShort());
                c1_v2 = (int) (ByteBuffer.wrap(data_c1, (i + 1) * bytes_per_sample, bytes_per_sample).order(ByteOrder.LITTLE_ENDIAN).getShort());
                c2_v1 = (int) (ByteBuffer.wrap(data_c2, i * bytes_per_sample, bytes_per_sample).order(ByteOrder.LITTLE_ENDIAN).getShort());
                c2_v2 = (int) (ByteBuffer.wrap(data_c2, (i + 1) * bytes_per_sample, bytes_per_sample).order(ByteOrder.LITTLE_ENDIAN).getShort());
            }
            if (table.containsKey(c1_v1)) {
                table.put(c1_v1, table.get(c1_v1) + 1);
            } else {
                table.put(c1_v1, 1);
            }
            if (table.containsKey(c1_v2)) {
                table.put(c1_v2, table.get(c1_v2) + 1);
            } else {
                table.put(c1_v2, 1);
            }
            if (table.containsKey(c2_v1)) {
                table.put(c2_v1, table.get(c2_v1) + 1);
            } else {
                table.put(c2_v1, 1);
            }
            if (table.containsKey(c2_v2)) {
                table.put(c2_v2, table.get(c2_v2) + 1);
            } else {
                table.put(c2_v2, 1);
            }
        }
        return table;
    }

    private static double calculateEntropy() {
        int sample_num_total = total_data.length / bytes_per_sample;
        Map<Integer, Integer> frequencyTable = calculate_freq();

        double entropy = 0.0;

        for (int sample : frequencyTable.keySet()) {
            double probability = (double) frequencyTable.get(sample) / sample_num_total;
            entropy -= probability * (Math.log(probability) / Math.log(2));
        }
        return entropy;
    }
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        int w = getWidth();
        int h = getHeight();
        g.setColor(Color.BLACK);
        g.fillRect(0, 0, w, h);
        
        double e = calculateEntropy();
        

        g.setColor(Color.white);
        g.drawString("the entropy of the audio samples : " + e, 30, 20);
        g.drawString("the average code word length: " + sample_rate + " Hz", 30, 60);
    }
}
