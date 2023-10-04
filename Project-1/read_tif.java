import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

import java.awt.*;
import java.awt.image.BufferedImage;

import java.util.Arrays;

public class read_tif extends JPanel{
    private static ByteOrder coding_order;
    private BufferedImage image;
    private static byte[] fileData;

    public read_tif(String imagePath) {
        try {
            image = ImageIO.read(new File(imagePath));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void draw(){
        repaint(); 
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(image, 0, 0, null);
    }


    public static void main(String[] args) {
        String inputFilePath = "./Q2/image1.tif";
        File inputFile = new File(inputFilePath);
        try {
            FileInputStream fileInputStream = new FileInputStream(inputFilePath);

            long fileSize = inputFile.length();
            byte[] fileData = new byte[(int)fileSize]; 
            fileInputStream.read(fileData);

            fileInputStream.close();

            byte[] Identifier = Arrays.copyOfRange(fileData, 0, 2);
            byte[] current_data = Arrays.copyOfRange(fileData, 4, fileData.length);
            if (Identifier[0] == (byte) 0x4D && Identifier[1] == (byte) 0x4D){
                coding_order = ByteOrder.BIG_ENDIAN;
            }else{
                coding_order = ByteOrder.LITTLE_ENDIAN;
            }

            byte[] IFDOffset = Arrays.copyOfRange(current_data, 0, 4);
            int offset = (int)(ByteBuffer.wrap(IFDOffset).order(coding_order).getInt());
            read_IFD(offset,fileData);

            
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int read_IFD(int offset,byte[] fileData){
        byte[] current_data = Arrays.copyOfRange(fileData, offset, fileData.length);
        byte[] tag_entry_count = Arrays.copyOfRange(current_data, 0, 2);
        current_data = Arrays.copyOfRange(current_data, 2, fileData.length);
        int tag_count = (int)(ByteBuffer.wrap(tag_entry_count).order(coding_order).getShort());

        for(int index =0 ; index< tag_count; index++){
            byte[] tag = Arrays.copyOfRange(current_data, 0, 12);
            current_data = Arrays.copyOfRange(current_data, 12, fileData.length);
            int tag_id = (int)(ByteBuffer.wrap(Arrays.copyOfRange(tag, 0, 2)).order(coding_order).getShort());
            int data_type = (int)(ByteBuffer.wrap(Arrays.copyOfRange(tag, 2, 4)).order(coding_order).getShort());
            int data_count = (int)(ByteBuffer.wrap(Arrays.copyOfRange(tag, 4, 8)).order(coding_order).getInt());
            //TODO fenqingkuangtaolun
            int data_offset = (int)(ByteBuffer.wrap(Arrays.copyOfRange(tag, 8, 12)).order(coding_order).getInt());
            switch (tag_id) {
                case 256: // ImageWidth
                    System.out.println("ImageWidth"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 257: // ImageLength
                    System.out.println("ImageLength"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 258: // BitsPerSample
                System.out.println("BitsPerSample"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 259: // Compression
                    System.out.println("Compression"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 262: //PhotometricInterpretation
                    System.out.println("PhotometricInterpretation"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 273: // StripOffsets
                    System.out.println("StripOffsets"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 277: // SamplePerPixel
                    System.out.println("SamplePerPixel"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 278: // RowsPerStrip
                    System.out.println("RowsPerStrip"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 279: // StripByteCounts
                    System.out.println("StripByteCounts"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 282: // XResolution
                    System.out.println("XResolution"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 283: // YResolution
                    System.out.println("YResolution"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 296: // Resolution Unit
                    System.out.println("Resolution Unit"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                case 284: // PlanarConfiguration
                    System.out.println("PlanarConfiguration"+" "+ tag_id +" " + data_type+ " "+data_count+ " "+data_offset);
                    break;
                default:
                    System.out.println(tag_id+" "+ data_type+ " "+data_count+ " "+data_offset);
                
            }
        }

        int net_tag_offset = (int)(ByteBuffer.wrap(Arrays.copyOfRange(current_data, 0, 4)).order(coding_order).getInt());;
        return net_tag_offset;
    }
}

