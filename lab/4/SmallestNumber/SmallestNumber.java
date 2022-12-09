package SmallestNumber;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;
import org.apache.hadoop.util.*;

import java.io.IOException;
import java.util.Iterator;

public class SmallestNumber {
    public static class Map extends MapReduceBase implements Mapper<LongWritable, Text, Text, IntWritable> {
        private Integer number;

        public void map(LongWritable key, Integer value, OutputCollector<IntWritable> output, Reporter reporter) throws IOException {
            number = value;
            output.collect(number);
        }
    }

    public static class Reduce extends MapReduceBase implements Reducer<Text, IntWritable, Text, IntWritable> {
        public void reduce(Text key, Iterator<IntWritable> values, OutputCollector<IntWritable> output, Reporter reporter) throws IOException {
            int num = 0;

            while (values.hasNext()) {
                int next = values.next().get();

                if (num > next) {
                    num = next;
                }
            }

            output.collect(num);
        }
    }

    public static void main(String[] args) throws Exception {
        JobConf conf = new JobConf(SmallestNumber.class);

        conf.setJobName("smallestnumber");
        conf.setOutputKeyClass(Integer.class);
        conf.setOutputValueClass(IntWritable.class);
        conf.setMapperClass(Map.class);
        conf.setCombinerClass(Reduce.class);
        conf.setReducerClass(Reduce.class);
        conf.setInputFormat(TextInputFormat.class);
        conf.setOutputFormat(TextOutputFormat.class);

        FileInputFormat.setInputPaths(conf, new Path(args[0]));
        FileOutputFormat.setOutputPath(conf, new Path(args[1]));
        JobClient.runJob(conf);
    }
}
