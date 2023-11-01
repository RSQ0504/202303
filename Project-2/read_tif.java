import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

import java.awt.*;
import java.awt.image.BufferedImage;

public class read_tif extends JPanel{
    private static BufferedImage image;
    private int page = 0;
    private static int width;
    private static int height;

    public read_tif(String imagePath) {
        try {
            image = ImageIO.read(new File(imagePath));
            width = image.getWidth();
            height = image.getHeight();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public BufferedImage Grayscale() {
        BufferedImage grey_image  = new BufferedImage(width, height,BufferedImage.TYPE_BYTE_GRAY);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int c_value = image.getRGB(x, y);
                int r = (c_value >> 16) & 0xFF; 
                int g = (c_value >> 8) & 0xFF;  
                int b = c_value & 0xFF;

                int gray = (int) (0.3*r + 0.59*g + 0.11*b);

                int grayPixel = (gray << 16) | (gray << 8) | gray;
                grey_image.setRGB(x, y, grayPixel);
            }
        }
        return grey_image;
    }

    public BufferedImage ReduceBright(BufferedImage i){
        BufferedImage copy;
        if (i.getType() == 0){
            copy  = new BufferedImage(width, height,BufferedImage.TYPE_INT_RGB);
        }else{
            copy  = new BufferedImage(width, height,i.getType());
        }
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int rgb = i.getRGB(x, y);

                int r = (rgb >> 16) & 0xFF;
                int g = (rgb >> 8) & 0xFF;
                int b = rgb & 0xFF;
                r = (int)(r * 0.5);
                g = (int)(g * 0.5);
                b = (int)(b * 0.5);
                int result = (r << 16) | (g << 8) | b;
                copy.setRGB(x, y, result);
            }
        }
        return copy;
    }

    private static BufferedImage orderedDither(BufferedImage image, int[][] mat) {
        BufferedImage result_image  = new BufferedImage(width, height,BufferedImage.TYPE_BYTE_GRAY);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int original_value = image.getRGB(x, y) & 0xFF;
                int dither_Value = mat[x % mat.length][y % mat[0].length];
                
                if (original_value%(mat.length*mat.length+1) > dither_Value) {
                    result_image.setRGB(x, y, 0xFFFFFF);
                } else {
                    result_image.setRGB(x, y, 0);
                }
            }
        }
        return result_image;
    }

    private static BufferedImage orderedDither_output(BufferedImage image) {
        int[][] mat = {
            {     0, 191,  48, 239,  12, 203,  60, 251,   3, 194,  51, 242,  15, 206,  63, 254  },
            {   127,  64, 175, 112, 139,  76, 187, 124, 130,  67, 178, 115, 142,  79, 190, 127  },
            {    32, 223,  16, 207,  44, 235,  28, 219,  35, 226,  19, 210,  47, 238,  31, 222  },
            {   159,  96, 143,  80, 171, 108, 155,  92, 162,  99, 146,  83, 174, 111, 158,  95  },
            {     8, 199,  56, 247,   4, 195,  52, 243,  11, 202,  59, 250,   7, 198,  55, 246  },
            {   135,  72, 183, 120, 131,  68, 179, 116, 138,  75, 186, 123, 134,  71, 182, 119  },
            {    40, 231,  24, 215,  36, 227,  20, 211,  43, 234,  27, 218,  39, 230,  23, 214  },
            {   167, 104, 151,  88, 163, 100, 147,  84, 170, 107, 154,  91, 166, 103, 150,  87  },
            {     2, 193,  50, 241,  14, 205,  62, 253,   1, 192,  49, 240,  13, 204,  61, 252  },
            {   129,  66, 177, 114, 141,  78, 189, 126, 128,  65, 176, 113, 140,  77, 188, 125  },
            {    34, 225,  18, 209,  46, 237,  30, 221,  33, 224,  17, 208,  45, 236,  29, 220  },
            {   161,  98, 145,  82, 173, 110, 157,  94, 160,  97, 144,  81, 172, 109, 156,  93  },
            {    10, 201,  58, 249,   6, 197,  54, 245,   9, 200,  57, 248,   5, 196,  53, 244  },
            {   137,  74, 185, 122, 133,  70, 181, 118, 136,  73, 184, 121, 132,  69, 180, 117  },
            {    42, 233,  26, 217,  38, 229,  22, 213,  41, 232,  25, 216,  37, 228,  21, 212  },
            {   169, 106, 153,  90, 165, 102, 149,  86, 168, 105, 152,  89, 164, 101, 148,  85  }
        };
        
        return orderedDither(image,mat);
    }

    private static double[] calculateCDF(BufferedImage image,char channel) {
        int[] count = new int[256];
        for(int i =0; i<256;i++){
            count[i] = 0;
        }
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int rgb = image.getRGB(x, y);
                int colorValue = 0;

                if (channel == 'r') {
                    colorValue = (rgb >> 16) & 0xFF; // Red channel
                } else if (channel == 'g') {
                    colorValue = (rgb >> 8) & 0xFF; // Green channel
                } else if (channel == 'b') {
                    colorValue = rgb & 0xFF; // Blue channel
                }
                count[colorValue]++;
            }
        }
        int sum = 0;
        for(int i =0; i<256;i++){
            sum+=count[i];
        }
        double[] cdf = new double[256];
        int step = 0;
        for(int i =0; i<256;i++){
            step+=count[i];
            cdf[i] = (double) step/sum;
            //System.out.println(cdf[i]);
        }
        return cdf;
    }

    private static BufferedImage atuoLevel_output(BufferedImage image) {
        BufferedImage result_image = new BufferedImage(width, height,BufferedImage.TYPE_INT_RGB);
        double[] cdf_r = calculateCDF(image,'r');
        double[] cdf_b = calculateCDF(image,'b');
        double[] cdf_g = calculateCDF(image,'g');

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int rgb = image.getRGB(x, y);

                int r = (rgb >> 16) & 0xFF;
                int g = (rgb >> 8) & 0xFF;
                int b = rgb & 0xFF;
                r = (int)(cdf_r[r] * 255.0);
                g = (int)(cdf_g[g] * 255.0);
                b = (int)(cdf_b[b] * 255.0);
                int result = (r << 16) | (g << 8) | b;
                result_image.setRGB(x, y, result);
            }
        }
        return result_image;
    }

    public void draw(){
        setLayout(new BorderLayout());
        repaint(); 
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        double scale_a = (double) width/350;
        double scale_b = (double) height/250;
        double s = (scale_a>scale_b)?scale_a:scale_b;
        //System.out.println(s);
        int scale = (int) Math.ceil(s);
        //System.out.println(scale);
        int scale_w=width/scale;
        int scale_h=height/scale;
        BufferedImage left;
        BufferedImage right;

        switch (page) {
            case 0:
                left = image;
                right = Grayscale();
                break;
            case 1:
                left = ReduceBright(image);
                right = ReduceBright(Grayscale());
                break;
            case 2:
                left = Grayscale();
                right = orderedDither_output(Grayscale());
                break;
            case 3:
                left = image;
                right = atuoLevel_output(image);
                break;
            default:
                left = image;
                right = Grayscale();
                page = 0;
                break;
        }
        page+=1;
        g.drawImage(left, 0, 0, scale_w, scale_h, null);
        g.drawImage(right, scale_w + 10, 0, scale_w, scale_h, null);
    }
}

