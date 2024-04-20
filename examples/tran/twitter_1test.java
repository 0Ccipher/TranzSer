package mbenchmarks;

import database.APIDatabase;

public class twitter_1test {
    
    public static void getFollowers(int uid) {
        var db = APIDatabase.getDatabase();
        try {
            db.begin();
            db.read("followers"+uid);
            db.commit();
        } catch (Exception e) {
            // Handle the exception
            
        }
    }
    
    public static void publishTweet(int uid) {
        var db = APIDatabase.getDatabase();
        try {
            db.begin();
            var a = db.read("tweets"+uid);
            int t = Integer.parseInt(a);
            t = t +1;
            db.write("tweets"+uid, ""+t);
            db.commit();
        } catch (Exception e) {
            // Handle the exception
            
        }
    }
    
    public static void getNewsfeed(int uid) {
        var db = APIDatabase.getDatabase();
        try {
            db.begin();
            var f = db.read("follows" + uid);
            var t = db.read("tweets" + uid);
            db.commit();
        } catch (Exception e) {
            // Handle the exception
            
        }
    }
    
    public static void follow(int uid, int fid) {
        var db = APIDatabase.getDatabase();
        try {
            db.begin();
            var followers_fid = db.read("followers" + fid);
            int followers_fid_value = Integer.parseInt(followers_fid);
            followers_fid_value = followers_fid_value + 1;
            db.write("followers" + fid, "" + followers_fid_value);

            var follows_uid = db.read("follows" + uid);
            int follows_uid_value = Integer.parseInt(follows_uid);
            follows_uid_value = follows_uid_value + 1;
            db.write("follows" + uid, "" + follows_uid_value);

            db.commit();
        } catch (Exception e) {
            // Handle the exception
            
        }
    }
    
    public static void getTimeline(int uid) {
        var db = APIDatabase.getDatabase();
        try {
            db.begin();
            db.read("tweets" + uid);
            db.commit();
        } catch (Exception e) {
            // Handle the exception
            
        }
    }
    
    public static void main(String[] args) throws InterruptedException {
        var db = APIDatabase.getDatabase();
        db.begin();
        db.write("users0","1");     
        db.write("users1","2");     
        db.write("users2","3");

        db.write("tweets0", "10");
        db.write("tweets1", "20");
        db.write("tweets2", "5");

        db.write("followers0", "0");
        db.write("followers1", "0");
        db.write("followers2", "1");

        db.write("follows0", "5");
        db.write("follows1", "2");
        db.write("follows2", "3");
      
        db.commit();
        
        Thread t1 = new Thread(() -> {
            publishTweet(1);
            getTimeline(1);
            // getTimeline(0);
        });

        Thread t2 = new Thread(() -> {
            publishTweet(1);
            // follow(0,1);
            getTimeline(1);
        });

        Thread t3 = new Thread(() -> {
            // follow(1,0);
            // getFollowers(0);
            // getTimeline(1);
            publishTweet(1);
        });

        // Thread t4 = new Thread(() -> {
        //     getFollowers(0);
        //     getFollowers(1);
        // });

        t1.start();
        t2.start();
        t3.start();
        // t4.join();
        t1.join();
        t2.join();
        t3.join();
        // t4.join();
    }
}


