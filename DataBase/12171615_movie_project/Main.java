import java.sql.*;

public class Main {

    // <delete_table>
    // method that deletes the all tuples in table corresponding to table_name
    static void delete_table(Connection _conn, String table_name) throws SQLException {
        System.out.println("Translated SQL : DELETE FROM " + table_name);
        PreparedStatement pstmt = _conn.prepareStatement("delete from "+table_name);
        pstmt.executeUpdate();
    }

    // <drop_table>
    // method that drop table corresponding to table_name
    static void drop_table(Connection _conn, String table_name) throws SQLException {
        System.out.println("Translated SQL : DROP TABLE IF EXISTS " + table_name);
        PreparedStatement pstmt = _conn.prepareStatement("drop table if exists "+table_name);
        pstmt.executeUpdate();
    }


    static void print_updated_table(Connection _conn, String table_name) throws SQLException {
        String str_for_stmt = "select * from " + table_name;
        Statement select_stmt = _conn.createStatement();
        ResultSet rs = select_stmt.executeQuery(str_for_stmt);

        ResultSetMetaData temp_rsmd = rs.getMetaData();
        System.out.println("\n******************* UPDATED TABLES *******************");
        System.out.println("<" + table_name + ">");
        for(int i = 1; i <= temp_rsmd.getColumnCount(); i++) {
            System.out.format("%-26s", "|" + temp_rsmd.getColumnName(i));
        }
        System.out.println();

        while(rs.next()) {
            for(int i = 1; i <= temp_rsmd.getColumnCount(); i++) {
                System.out.format("%-26s", "|" + rs.getObject(i));
            }
            System.out.println();
        }
    }


    // <update_movie_avgRate>
    // method that updates the avgRate of movie that has movieID corresponding to movie_id
    static void update_movie_avgRate(Connection _conn, int movie_id) throws SQLException {
        Statement select_stmt = _conn.createStatement();
        Statement update_stmt = _conn.createStatement();

        String str_for_stmt;

        double count_of_movieID = 0;
        double sum_of_rate = 0;
        double avg_rate=0;
        // String movie_name = null;

        str_for_stmt = "select count(*) from customerRate where movieID = '" + movie_id + "'";
        ResultSet rs = select_stmt.executeQuery(str_for_stmt);
        while (rs.next()) {
            count_of_movieID = rs.getInt(1);
        }

        str_for_stmt =  "select sum(rate) from customerRate where movieID = '" + movie_id + "'";
        rs = select_stmt.executeQuery(str_for_stmt);
        while (rs.next()) {
            sum_of_rate = rs.getInt(1);
        }

        if(count_of_movieID!=0)
            avg_rate = sum_of_rate/count_of_movieID;
        else
            avg_rate = 0;

        str_for_stmt = "update movie set avgRate = " + avg_rate + "where movieID = '" + movie_id + "'";
        update_stmt.executeUpdate(str_for_stmt);
    }




    // <Insert_No2>
    // method that solves 2nd statements and print
    // because each 2nd statements are almost same operations
    static void insert_No2(String type, Connection _conn, String str_typeName, String str_awardName, int award_year) throws SQLException {
        // type - actor or director or movie
        Statement select_stmt = _conn.createStatement(); // Statement Object for execute select sql
        Statement insert_stmt = _conn.createStatement(); // Statement Object for execute insert sql
        String str_insert;
        String str_select;

        System.out.println("Statement : " + str_typeName + " won the \"" + str_awardName + "\" award in " + award_year);

        // find each type's id(actorID or directorID or movieID) that has Name corresponding to str_typeName
        // and assign to type_id variable.
        System.out.println("Translated SQL : SELECT " + type + "ID FROM " + type + " WHERE " + type + "Name = \"" + str_typeName + "\"");
        str_select = "select " + type + "ID from " + type + " where " + type + "Name = '" + str_typeName + "';";
        ResultSet rs = select_stmt.executeQuery(str_select);
        int type_id = 0; //
        while (rs.next()) {
            type_id = rs.getInt(1);
        }

        // when needed to add new award
        // str_awardName is not exists in award
        boolean award_exists = false;
        String find_awardName = "select awardName from award";
        rs = select_stmt.executeQuery(find_awardName);
        String award_name = null; //
        while (rs.next()) {
            award_name = rs.getString(1);
            if (award_name.compareTo(str_awardName) == 0) { // 문자열 string 비교 -> ==을 통해서 안됨
                award_exists = true;
            }
        }

        if (!award_exists) { // 입력받은 str_awardName이 award table에 존재하지 않을 때, 이를 table에 추가
            // 현재 award table에 들어있는 tuple의 개수를 알아내는 과정
            String str_find_award = "select count(awardID) from award";
            rs = select_stmt.executeQuery(str_find_award);
            int award_num = 0; //
            while (rs.next()) {
                award_num = rs.getInt(1);
            }

            // str_awardName에 해당하는 awardName을 award table에 저장
            System.out.println("Translated SQL : INSERT INTO award (awardID, awardName) VALUES (" + (award_num + 1) + " , \"" + str_awardName + "\")");
            str_insert = "INSERT INTO award VALUES (" + (award_num + 1) + ", '" + str_awardName + "');";
            insert_stmt.executeUpdate(str_insert);
        }

        System.out.println("Translated SQL : SELECT awardID FROM award WHERE awardName = \"" + str_awardName + "\"");
        //  str_awardName에 해당하는 awardName을 가지고 있는 award table의 tuple의 awardID를 award_id에 저장
        str_select = "select awardID from award where awardName = '" + str_awardName + "'";
        rs = select_stmt.executeQuery(str_select);
        int award_id = 0;
        while (rs.next()) {
            award_id = rs.getInt(1);
        }

        System.out.println("Translated SQL : INSERT INTO actorObtain VALUES (" + type_id + ", " + award_id + ", " + award_year + ")");
        // typeObtain(type_id, award_id, year)
        str_insert = "Insert into " + type + "Obtain values (" + type_id + ", " + award_id + ", " + award_year + ");";
        insert_stmt.executeUpdate(str_insert);

        // print the updated tables - typeObtain table -> actorObtain,
        str_select = "select * from " + type +"Obtain order by " + type + "ID";
        rs = select_stmt.executeQuery(str_select);
        print_updated_table(_conn, type+"Obtain");

        if (!award_exists){
            // print the updated tables - award table
            str_select = "select * from award";
            rs = select_stmt.executeQuery(str_select);
            print_updated_table(_conn, "award");}

        System.out.println("\n\n");
    }


// ----------------------------------------------------------------main method----------------------------------------------------------------//

    public static void main(String[] args) throws Exception {
        try {
            Class.forName("org.postgresql.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println("Where is your PostgreSQL JDBC Driver? Include in your library path!");
            e.printStackTrace();
            return;
        }

        System.out.println("PostgreSQL JDBC Driver Registered!");

        // DBMS 서버와의 연결을 위한 Connection 객체 생성
        Connection connection = null;

        try {
            connection = DriverManager.getConnection(
                    "jdbc:postgresql://127.0.0.1:5432/project_movie", "postgres", "cse3207");
        } catch (SQLException e) {
            System.out.println("Connection Failed! Check output console");
            e.printStackTrace();
            return;
        }

        if (connection != null) {
            System.out.println(connection);
            System.out.println("You made it, take control your database now!");
        } else {
            System.out.println("Failed to make connection!");
        }

//----------------------------------------------------------------Create all tables----------------------------------------------------------------//

        // director
        PreparedStatement pStmt_ct = connection.prepareStatement("create table if not exists director" +
                " (directorID int, " +
                "directorName varchar(20) , " +
                "dateOfBirth DATE, " +
                "dateOfDeath DATE," +
                "primary key(directorID));");
        pStmt_ct.execute();

        // actor
        pStmt_ct = connection.prepareStatement(
                "create table if not exists actor " +
                        "(actorID int, " +
                        "actorName varchar(20), " +
                        "dateOfBirth DATE, " +
                        "dateOfDeath DATE, " +
                        "gender varchar(7) check (gender in (\'Male\', \'Female\'))," +
                        " primary key(actorID));");
        pStmt_ct.execute();

        // movie
        pStmt_ct = connection.prepareStatement(
                "create table if not exists movie " +
                        "(movieID int, " +
                        "movieName varchar(20), " +
                        "relaseYear int, " +
                        "relaseMonth int, " +
                        "releaseDate int, " +
                        "publisherName varchar(30), " +
                        "avgRate numeric(4,2)," +
                        "primary key(movieID)) ");
        // a value of ‘avgRate’ column should be automatically calculated when a customer gives a rate
        pStmt_ct.execute();

        // award
        pStmt_ct = connection.prepareStatement("create table if not exists award " +
                "(awardID int, " +
                "awardName varchar(30)," +
                "primary key(awardID));");
        pStmt_ct.execute();

        // genre
        pStmt_ct = connection.prepareStatement("create table if not exists genre " +
                "(genreName varchar(20), " +
                "primary key(genreName));");
        pStmt_ct.execute();

        // movieGenre
        pStmt_ct = connection.prepareStatement(
                "create table if not exists movieGenre " +
                        "(movieID int, " +
                        "genreName varchar(20), " +
                        "primary key(movieID, genreName), " +
                        "foreign key(movieID) references movie on delete cascade, " +
                        "foreign key(genreName) references genre on delete cascade);");
        pStmt_ct.execute();

        // movieObtain
        pStmt_ct = connection.prepareStatement(
                "create table if not exists movieObtain " +
                        "(movieID int, " +
                        "awardID int, " +
                        "year int, " +
                        "primary key(movieID, awardID), " +
                        "foreign key(movieID) references movie on delete cascade," +
                        " foreign key(awardID) references award on delete cascade);");
        pStmt_ct.execute();

        // actorObtain
        pStmt_ct = connection.prepareStatement(
                "create table if not exists actorObtain " +
                        "(actorID int, " +
                        "awardID int, " +
                        "year int, " +
                        "primary key(actorID, awardID), " +
                        "foreign key(actorID) references actor on delete cascade," +
                        "foreign key(awardID) references award on delete cascade);");
        pStmt_ct.execute();

        // directorObtain
        pStmt_ct = connection.prepareStatement(
                "create table if not exists directorObtain " +
                        "(directorID int, " +
                        "awardID int, " +
                        "year int, " +
                        "primary key(directorID, awardID), " +
                        "foreign key(directorID) references director on delete cascade," +
                        "foreign key(awardID) references award on delete cascade);");
        pStmt_ct.execute();

        // casting
        pStmt_ct = connection.prepareStatement(
                "create table if not exists casting " +
                        "(movieID int, " +
                        "actorID int, " +
                        "role varchar(20), " +
                        "primary key(movieID, actorID),  " +
                        "foreign key(movieID) references movie on delete cascade," +
                        "foreign key(actorID) references actor on delete cascade);");
        pStmt_ct.execute();

        // make
        pStmt_ct = connection.prepareStatement(
                "create table if not exists make" +
                        "(movieID int, " +
                        "directorID int, " +
                        "primary key(movieID, directorID), " +
                        "foreign key(movieID) references movie on delete cascade," +
                        "foreign key(directorID) references director on delete cascade);");
        pStmt_ct.execute();

        // customer
        pStmt_ct = connection.prepareStatement(
                "create table if not exists customer " +
                        "(customerID int, " +
                        "customerName varchar(30), " +
                        "dateOfBirth DATE, " +
                        "gender varchar(7) check (gender in (\'Male\', \'Female\')), " +
                        "primary key(customerID));");
        pStmt_ct.execute();

        // customerRate
        pStmt_ct = connection.prepareStatement(
                "create table if not exists customerRate " +
                        "(customerID int, " +
                        "movieID int, " +
                        "rate int, " +
                        "primary key(customerID, movieID) , " +
                        "foreign key(customerID) references customer on delete cascade," +
                        "foreign key(movieID) references movie on delete cascade);");
        pStmt_ct.execute();

        System.out.println("\nTable created!");

//----------------------------------------------------------------Insert Initial data----------------------------------------------------------------//

        // director
        PreparedStatement pStmt_insert = connection.prepareStatement(" Insert into director values (?, ?, ?, ?);");
        pStmt_insert.setInt(1, 1);
        pStmt_insert.setString(2, "Tim Burton");
        pStmt_insert.setDate(3, Date.valueOf("1958-8-25"));
        pStmt_insert.setDate(4, null);
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 2);
        pStmt_insert.setString(2, "David Fincher");
        pStmt_insert.setDate(3, Date.valueOf("1962-8-28"));
        pStmt_insert.setDate(4, null);
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 3);
        pStmt_insert.setString(2, "Christopher Nolan");
        pStmt_insert.setDate(3, Date.valueOf("1970-7-30"));
        pStmt_insert.setDate(4, null);
        pStmt_insert.executeUpdate();

        // actor
        pStmt_insert = connection.prepareStatement(" Insert into actor values (?, ?, ?, ?, ?);");
        pStmt_insert.setInt(1, 1);
        pStmt_insert.setString(2, "Johnny Depp");
        pStmt_insert.setDate(3, Date.valueOf("1958-8-25"));
        pStmt_insert.setDate(4, null);
        pStmt_insert.setString(5, "Male");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 2);
        pStmt_insert.setString(2, "Winona Ryder");
        pStmt_insert.setDate(3, Date.valueOf("1971-10-29"));
        pStmt_insert.setDate(4, null);
        pStmt_insert.setString(5, "Female");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 3);
        pStmt_insert.setString(2, "Mia Wasikowska");
        pStmt_insert.setDate(3, Date.valueOf("1989-10-14"));
        pStmt_insert.setDate(4, null);
        pStmt_insert.setString(5, "Female");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 4);
        pStmt_insert.setString(2, "Christian Bale");
        pStmt_insert.setDate(3, Date.valueOf("1974-1-30"));
        pStmt_insert.setDate(4, null);
        pStmt_insert.setString(5, "Male");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 5);
        pStmt_insert.setString(2, "Heath Ledger");
        pStmt_insert.setDate(3, Date.valueOf("1979-4-4"));
        pStmt_insert.setDate(4, Date.valueOf("2008-1-22"));
        pStmt_insert.setString(5, "Male");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 6);
        pStmt_insert.setString(2, "Jesse Eisenberg");
        pStmt_insert.setDate(3, Date.valueOf("1983-10-5"));
        pStmt_insert.setDate(4, null);
        pStmt_insert.setString(5, "Male");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 7);
        pStmt_insert.setString(2, "Justin Timberlake");
        pStmt_insert.setDate(3, Date.valueOf("1981-1-31"));
        pStmt_insert.setDate(4, null);
        pStmt_insert.setString(5, "Male");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 8);
        pStmt_insert.setString(2, "Fionn Whitehead");
        pStmt_insert.setDate(3, Date.valueOf("1996-7-18"));
        pStmt_insert.setDate(4, null);
        pStmt_insert.setString(5, "Male");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 9);
        pStmt_insert.setString(2, "Tom Hardy");
        pStmt_insert.setDate(3, Date.valueOf("1977-9-15"));
        pStmt_insert.setDate(4, null);
        pStmt_insert.setString(5, "Male");
        pStmt_insert.executeUpdate();

        // customer
        pStmt_insert = connection.prepareStatement(" Insert into customer values (?, ?, ?, ?);");
        pStmt_insert.setInt(1, 1);
        pStmt_insert.setString(2, "Ethan");
        pStmt_insert.setDate(3, Date.valueOf("1997-11-14"));
        pStmt_insert.setString(4, "Male");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 2);
        pStmt_insert.setString(2, "John");
        pStmt_insert.setDate(3, Date.valueOf("1978-1-23"));
        pStmt_insert.setString(4, "Male");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 3);
        pStmt_insert.setString(2, "Hayden");
        pStmt_insert.setDate(3, Date.valueOf("1980-5-4"));
        pStmt_insert.setString(4, "Female");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 4);
        pStmt_insert.setString(2, "Jill");
        pStmt_insert.setDate(3, Date.valueOf("1981-4-17"));
        pStmt_insert.setString(4, "Female");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 5);
        pStmt_insert.setString(2, "Bell");
        pStmt_insert.setDate(3, Date.valueOf("1990-5-14"));
        pStmt_insert.setString(4, "Female");
        pStmt_insert.executeUpdate();


        // Insert given genreName into genre table
        pStmt_insert = connection.prepareStatement("Insert into genre values (?) ;");
        pStmt_insert.setString(1, "Fantasy");
        pStmt_insert.executeUpdate();

        pStmt_insert.setString(1, "Romance");
        pStmt_insert.executeUpdate();

        pStmt_insert.setString(1, "Adventure");
        pStmt_insert.executeUpdate();

        pStmt_insert.setString(1, "Family");
        pStmt_insert.executeUpdate();

        pStmt_insert.setString(1, "Drama");
        pStmt_insert.executeUpdate();

        pStmt_insert.setString(1, "Action");
        pStmt_insert.executeUpdate();

        pStmt_insert.setString(1, "Mystery");
        pStmt_insert.executeUpdate();

        pStmt_insert.setString(1, "Thriller");
        pStmt_insert.executeUpdate();

        pStmt_insert.setString(1, "War");
        pStmt_insert.executeUpdate();


        //---------- Movie Initial data 1 ------------//
        // movie table에 입력
        pStmt_insert = connection.prepareStatement(" Insert into movie values (?, ?, ?, ?, ?, ?, ?);");
        pStmt_insert.setInt(1, 1);
        pStmt_insert.setString(2, "Edward Scissorhands");
        pStmt_insert.setInt(3, 1991);
        pStmt_insert.setInt(4, 6);
        pStmt_insert.setInt(5, 29);
        pStmt_insert.setString(6, "20th Century Fox Presents");
        pStmt_insert.setInt(7, 0);
        pStmt_insert.executeUpdate();

        // make(1, 1) Edward Scissorhands, Tim Burton
        pStmt_insert = connection.prepareStatement(" Insert into make values (?, ?);");
        pStmt_insert.setInt(1, 1);
        pStmt_insert.setInt(2, 1);
        pStmt_insert.executeUpdate();

        // casting(1,1,Main actor) Edward Scissorhands, Johnny Depp
        pStmt_insert = connection.prepareStatement(" Insert into casting values (?, ?, ?);");
        pStmt_insert.setInt(1, 1);
        pStmt_insert.setInt(2, 1);
        pStmt_insert.setString(3, "Main actor");
        pStmt_insert.executeUpdate();

        // casting(1,2,Main actor) Edward Scissorhands, Winona Ryderr
        pStmt_insert.setInt(1, 1);
        pStmt_insert.setInt(2, 2);
        pStmt_insert.setString(3, "Main actor");
        pStmt_insert.executeUpdate();


        // movieGenre(1, Fantasy), movieGenre(1, Romance),
        pStmt_insert = connection.prepareStatement(" Insert into movieGenre values (?, ?);");
        pStmt_insert.setInt(1, 1);
        pStmt_insert.setString(2, "Fantasy");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 1);
        pStmt_insert.setString(2, "Romance");
        pStmt_insert.executeUpdate();


        //---------- Movie Initial data 2 ------------//
        // movie table에 입력
        pStmt_insert = connection.prepareStatement(" Insert into movie values (?, ?, ?, ?, ?, ?, ?);");
        pStmt_insert.setInt(1, 2);
        pStmt_insert.setString(2, "Alice In Wonderland");
        pStmt_insert.setInt(3, 2010);
        pStmt_insert.setInt(4, 3);
        pStmt_insert.setInt(5, 4);
        pStmt_insert.setString(6, "Korea Sony Pictures");
        pStmt_insert.setInt(7, 0);
        pStmt_insert.executeUpdate();

        // make(2, 1) Alice In Wonderland, Tim Burton
        pStmt_insert = connection.prepareStatement(" Insert into make values (?, ?);");
        pStmt_insert.setInt(1, 2);
        pStmt_insert.setInt(2, 1);
        pStmt_insert.executeUpdate();

        // casting(2,1,Main actor) Alice In Wonderland, Johnny Depp
        pStmt_insert = connection.prepareStatement(" Insert into casting values (?, ?, ?);");
        pStmt_insert.setInt(1, 2);
        pStmt_insert.setInt(2, 1);
        pStmt_insert.setString(3, "Main actor");
        pStmt_insert.executeUpdate();

        // casting(2,3,Main actor) Alice In Wonderland, Mia Wasikowska
        pStmt_insert.setInt(1, 2);
        pStmt_insert.setInt(2, 3);
        pStmt_insert.setString(3, "Main actor");
        pStmt_insert.executeUpdate();

        // movieGenre(2, Fantasy), movieGenre(2, Adventure), movieGenre(2, Family)
        pStmt_insert = connection.prepareStatement(" Insert into movieGenre values (?, ?);");
        pStmt_insert.setInt(1, 2);
        pStmt_insert.setString(2, "Fantasy");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 2);
        pStmt_insert.setString(2, "Adventure");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 2);
        pStmt_insert.setString(2, "Family");
        pStmt_insert.executeUpdate();


        //---------- Movie Initial data 3 ------------//
        // movie table에 입력
        pStmt_insert = connection.prepareStatement(" Insert into movie values (?, ?, ?, ?, ?, ?, ?);");
        pStmt_insert.setInt(1, 3);
        pStmt_insert.setString(2, "The Social Network");
        pStmt_insert.setInt(3, 2010);
        pStmt_insert.setInt(4, 11);
        pStmt_insert.setInt(5, 18);
        pStmt_insert.setString(6, "Korea Sony Pictures");
        pStmt_insert.setInt(7, 0);
        pStmt_insert.executeUpdate();

        // make(3, 2) Alice In Wonderland, David Fincher
        pStmt_insert = connection.prepareStatement(" Insert into make values (?, ?);");
        pStmt_insert.setInt(1, 3);
        pStmt_insert.setInt(2, 2);
        pStmt_insert.executeUpdate();

        // casting(3,6,Main actor) The Social Network, Jesse Eisenberg
        pStmt_insert = connection.prepareStatement(" Insert into casting values (?, ?, ?);");
        pStmt_insert.setInt(1, 3);
        pStmt_insert.setInt(2, 6);
        pStmt_insert.setString(3, "Main actor");
        pStmt_insert.executeUpdate();

        // casting(3,7,Supporting actor) The Social Network, Justin Timberlake
        pStmt_insert.setInt(1, 3);
        pStmt_insert.setInt(2, 7);
        pStmt_insert.setString(3, "Supporting actor");
        pStmt_insert.executeUpdate();

        // movieGenre(3, Drama)
        pStmt_insert = connection.prepareStatement(" Insert into movieGenre values (?, ?);");
        pStmt_insert.setInt(1, 3);
        pStmt_insert.setString(2, "Drama");
        pStmt_insert.executeUpdate();


        //---------- Movie Initial data 4 ------------//
        // movie table에 입력
        pStmt_insert = connection.prepareStatement(" Insert into movie values (?, ?, ?, ?, ?, ?, ?);");
        pStmt_insert.setInt(1, 4);
        pStmt_insert.setString(2, "The Dark Knight");
        pStmt_insert.setInt(3, 2008);
        pStmt_insert.setInt(4, 8);
        pStmt_insert.setInt(5, 6);
        pStmt_insert.setString(6, "Warner Brothers Korea");
        pStmt_insert.setInt(7, 0);
        pStmt_insert.executeUpdate();

        // make(4, 3) The Dark Knight, Christopher Nolan
        pStmt_insert = connection.prepareStatement(" Insert into make values (?, ?);");
        pStmt_insert.setInt(1, 4);
        pStmt_insert.setInt(2, 3);
        pStmt_insert.executeUpdate();

        // casting(4,4,Main actor) The Dark Knight, Christian Bale
        pStmt_insert = connection.prepareStatement(" Insert into casting values (?, ?, ?);");
        pStmt_insert.setInt(1, 4);
        pStmt_insert.setInt(2, 4);
        pStmt_insert.setString(3, "Main actor");
        pStmt_insert.executeUpdate();

        // casting(4,5,Main actor) The Dark Knight, Heath Ledger
        pStmt_insert.setInt(1, 4);
        pStmt_insert.setInt(2, 5);
        pStmt_insert.setString(3, "Main actor");
        pStmt_insert.executeUpdate();

        // movieGenre(4, Action), movieGenre(4, Drama), movieGenre(4, Mystery), movieGenre(4, Thriller)
        pStmt_insert = connection.prepareStatement(" Insert into movieGenre values (?, ?);");
        pStmt_insert.setInt(1, 4);
        pStmt_insert.setString(2, "Action");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 4);
        pStmt_insert.setString(2, "Drama");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 4);
        pStmt_insert.setString(2, "Mystery");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 4);
        pStmt_insert.setString(2, "Thriller");
        pStmt_insert.executeUpdate();


        //---------- Movie Initial data 5 ------------//
        // movie table에 입력
        pStmt_insert = connection.prepareStatement(" Insert into movie values (?, ?, ?, ?, ?, ?, ?);");
        pStmt_insert.setInt(1, 5);
        pStmt_insert.setString(2, "Dunkirk");
        pStmt_insert.setInt(3, 2017);
        pStmt_insert.setInt(4, 7);
        pStmt_insert.setInt(5, 13);
        pStmt_insert.setString(6, "Warner Brothers Korea");
        pStmt_insert.setInt(7, 0);
        pStmt_insert.executeUpdate();

        // make(5, 3) Dunkirk, Christopher Nolan
        pStmt_insert = connection.prepareStatement(" Insert into make values (?, ?);");
        pStmt_insert.setInt(1, 5);
        pStmt_insert.setInt(2, 3);
        pStmt_insert.executeUpdate();

        // casting(5,8,Main actor) Dunkirk, Fionn Whitehead
        pStmt_insert = connection.prepareStatement(" Insert into casting values (?, ?, ?);");
        pStmt_insert.setInt(1, 5);
        pStmt_insert.setInt(2, 8);
        pStmt_insert.setString(3, "Main actor");
        pStmt_insert.executeUpdate();

        // casting(5,9,Supporting actor) Dunkirk, Tom Hardy
        pStmt_insert.setInt(1, 5);
        pStmt_insert.setInt(2, 9);
        pStmt_insert.setString(3, "Supporting actor");
        pStmt_insert.executeUpdate();

        // movieGenre(5, Action), movieGenre(5, Drama), movieGenre(5, Thriller), movieGenre(5, War)
        pStmt_insert = connection.prepareStatement(" Insert into movieGenre values (?, ?);");
        pStmt_insert.setInt(1, 5);
        pStmt_insert.setString(2, "Action");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 5);
        pStmt_insert.setString(2, "Drama");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 5);
        pStmt_insert.setString(2, "Thriller");
        pStmt_insert.executeUpdate();

        pStmt_insert.setInt(1, 5);
        pStmt_insert.setString(2, "War");
        pStmt_insert.executeUpdate();

        System.out.println("\nInitial data inserted!");

//--------------------------------Initial data 입력 완료----------------------------------------------------//

        // No 2 Statements
        System.out.println("\n------------------------------------------------- No 2 Statements -------------------------------------------------");
        // actor
        insert_No2("actor", connection, "Winona Ryder", "Best supporting actor", 1994);
        insert_No2("actor", connection, "Tom Hardy", "Best supporting actor", 2018);
        insert_No2("actor", connection, "Heath Ledger", "Best villain actor", 2009);
        insert_No2("actor", connection, "Johnny Depp", "Best main actor", 2011);
        // movie
        insert_No2("movie", connection, "Edward Scissorhands", "Best fantasy movie", 1991);
        insert_No2("movie", connection, "Alice In Wonderland", "Best fantasy movie", 2011);
        insert_No2("movie", connection, "The Dark Knight", "Best picture", 2009);
        // director
        insert_No2("director", connection, "Christopher Nolan", "Best director", 2018);

        // No 3 Statements
        System.out.println("------------------------------------------------- No 3 Statements -------------------------------------------------");

        // 3.1 " Ethan rates 5 to "Dunkirk" "
        System.out.println("Statement : Ethan rates 5 to \"Dunkirk\"");
        System.out.println("Translated SQL : SELECT customerID FROM customer WHERE customerName = 'Ethan'");
        PreparedStatement find_customer_ID = connection.prepareStatement( " select customerID from customer where customerName = (?)");
        find_customer_ID.setString(1, "Ethan");

        ResultSet rs = find_customer_ID.executeQuery();
        int customer_id = 0; //
        while (rs.next()) {
            customer_id = rs.getInt(1);
        }

        System.out.println("Translated SQL : SELECT movieID FROM movie WHERE movieName = 'Dunkirk'");
        PreparedStatement pstmt_all_use = connection.prepareStatement( " select movieID from movie where movieName = 'Dunkirk'");
        rs = pstmt_all_use.executeQuery();
        int movie_id = 0;
        while (rs.next()) {
            movie_id = rs.getInt(1);
        }

        System.out.println("Translated SQL : INSERT INTO customerRate VALUES (" + customer_id + ", " + movie_id + ", 5)");
        pstmt_all_use = connection.prepareStatement( "INSERT INTO customerRate VALUES (" + customer_id + ", " + movie_id + ", 5)");
        pstmt_all_use.executeUpdate();

        // update avgRate
        update_movie_avgRate(connection, movie_id);

        // print updated customerRate table and movie table
        print_updated_table(connection, "customerRate");
        print_updated_table(connection, "movie");

        // 3.2 " Bell rates 5 to the movies whose director is "Tim Burton" "
        System.out.println("\n\n\nStatement : Bell rates 5 to the movies whose director is \"Tim Burton\"");
        System.out.println("Translated SQL : SELECT customerID FROM customer WHERE customerName = 'Bell'");
        find_customer_ID.setString(1, "Bell");

        rs = find_customer_ID.executeQuery();
        while (rs.next()) {
            customer_id = rs.getInt(1);
        }

        System.out.println("Translated SQL : SELECT directorID FROM director WHERE directorName = 'Tim Burton'");
        pstmt_all_use = connection.prepareStatement( " select directorID from director where directorName = 'Tim Burton'");
        rs = pstmt_all_use.executeQuery();
        int director_id = 0;
        while (rs.next()) {
            director_id = rs.getInt(1);
        }

        System.out.println("Translated SQL : SELECT movieID FROM make WHERE directorID = '" + director_id + "'");
        pstmt_all_use = connection.prepareStatement( " select movieID from make where directorID = '" + director_id +"'");
        rs = pstmt_all_use.executeQuery();
        movie_id = 0;
        while (rs.next()) {
            movie_id = rs.getInt(1); // movie_id = 1, 2
            System.out.println("Translated SQL : INSERT INTO customerRate VALUES (" + customer_id + ", " + movie_id + ", 5)");
            pstmt_all_use = connection.prepareStatement("INSERT INTO customerRate VALUES (" + customer_id + ", " + movie_id + ", 5)");
            pstmt_all_use.executeUpdate();
            update_movie_avgRate(connection, movie_id);
        }

        print_updated_table(connection, "customerRate");
        print_updated_table(connection, "movie");

        // 3.3 "Jill rates 4 to the movies whose main actor is female"
        System.out.println("\n\n\nStatement : Jill rates 4 to the movies whose main actor is female");
        System.out.println("Translated SQL : SELECT customerID FROM customer WHERE customerName = 'Jill'");
        find_customer_ID.setString(1, "Jill");

        rs = find_customer_ID.executeQuery();
        while (rs.next()) {
            customer_id = rs.getInt(1);
        }

        System.out.println("Translated SQL : SELECT movieID FROM actor NATURAL JOIN casting WHERE role = 'Main actor' AND gender = 'Female'");
        pstmt_all_use = connection.prepareStatement( "select movieID from actor natural join casting where role = 'Main actor' and gender = 'Female'");
        rs = pstmt_all_use.executeQuery();
        while (rs.next()) {
            movie_id = rs.getInt(1); // movie_id = 1, 2
            System.out.println("Translated SQL : INSERT INTO customerRate VALUES (" + customer_id + ", " + movie_id + ", 4)");
            pstmt_all_use = connection.prepareStatement("INSERT INTO customerRate VALUES (" + customer_id + ", " + movie_id + ", 4)");
            pstmt_all_use.executeUpdate();
            update_movie_avgRate(connection, movie_id);
        }

        print_updated_table(connection, "customerRate");
        print_updated_table(connection, "movie");

        // 3.4 "Hayden rates 4 to the fantasy movies"
        System.out.println("\n\n\nStatement : Hayden rates 4 to the fantasy movies");
        System.out.println("Translated SQL : SELECT customerID FROM customer WHERE customerName = 'Hayden'");
        find_customer_ID.setString(1, "Hayden");

        rs = find_customer_ID.executeQuery();
        while (rs.next()) {
            customer_id = rs.getInt(1);
        }

        System.out.println("Translated SQL : SELECT movieID FROM movie NATURAL JOIN movieGenre WHERE genreName = 'Fantasy'");
        pstmt_all_use = connection.prepareStatement( "select movieID from movie natural join movieGenre where genreName = 'Fantasy'");
        rs = pstmt_all_use.executeQuery();
        while (rs.next()) {
            movie_id = rs.getInt(1); // movie_id = 1, 2
            System.out.println("Translated SQL : INSERT INTO customerRate VALUES (" + customer_id + ", " + movie_id + ", 4)");
            pstmt_all_use = connection.prepareStatement("INSERT INTO customerRate VALUES (" + customer_id + ", " + movie_id + ", 4)");
            pstmt_all_use.executeUpdate();
            update_movie_avgRate(connection, movie_id);
        }

        print_updated_table(connection, "customerRate");
        print_updated_table(connection, "movie");

        // 3.5 "John rates 5 to the movies whose director won the "Best director" award"
        System.out.println("\n\n\nStatement : John rates 5 to the movies whose director won the \"Best director\" award");
        System.out.println("Translated SQL : SELECT customerID FROM customer WHERE customerName = 'John'");
        find_customer_ID.setString(1, "John");

        rs = find_customer_ID.executeQuery();
        while (rs.next()) {
            customer_id = rs.getInt(1);
        }

        System.out.println("Translated SQL : SELECT movieID FROM directorObtain NATURAL JOIN award NATURAL JOIN make WHERE awardName = 'Best director'");
        pstmt_all_use = connection.prepareStatement( "select movieID from directorObtain natural join award natural join make where awardName = 'Best director'");
        rs = pstmt_all_use.executeQuery();
        while (rs.next()) {
            movie_id = rs.getInt(1); // movie_id = 4, 5
            System.out.println("Translated SQL : INSERT INTO customerRate VALUES (" + customer_id + ", " + movie_id + ", 5)");
            pstmt_all_use = connection.prepareStatement("INSERT INTO customerRate VALUES (" + customer_id + ", " + movie_id + ", 5)");
            pstmt_all_use.executeUpdate();
            update_movie_avgRate(connection, movie_id);
        }

        print_updated_table(connection, "customerRate");
        print_updated_table(connection, "movie");

        // No.4 Statement
        System.out.println("\n\n\n------------------------------------------------- No 4 Statement -------------------------------------------------");
        System.out.println("Statement : Select the names of the movies whose actor are dead");
        System.out.println("Translated SQL : SELECT movieName FROM actor NATURAL JOIN casting NATURAL JOIN movie where dateofDeath IS NOT NULL");
        pstmt_all_use = connection.prepareStatement( "select movieName\n" +
                "from actor natural join casting natural join movie\n" +
                "where dateofDeath IS NOT NULL");
        rs = pstmt_all_use.executeQuery();

        ResultSetMetaData rsmd = rs.getMetaData();
        System.out.println("\n******************* Result *******************");
        for(int i = 1; i <= rsmd.getColumnCount(); i++) {
            System.out.format("%-26s", "|" + rsmd.getColumnName(i));
        }
        System.out.println();

        while(rs.next()) {
            for(int i = 1; i <= rsmd.getColumnCount(); i++) {
                System.out.format("%-26s", "|" + rs.getObject(i));
            }
            System.out.println();
        }

        // No.5 Statement
        System.out.println("\n\n\n------------------------------------------------- No 5 Statement -------------------------------------------------");
        System.out.println("Statement : Select the names of the directors who cast the same actor more than once");
        System.out.println("Translated SQL : \nwith actor_more_than_once(actorID) as\n" + // actor_more_than_once는 2번이상 casting 된 actor의 actorID를 나타낸다.
                "(select actorID\n" +
                "from casting\n" +
                "group by actorID\n" +
                "having count(*)>1\n" +
                "order by actorID), \n" +
                "\n" +
                "director_cast(directorID) as\n" + // director_cast는 2번이상 casting된 actor 중, 모두 같은 director에게 casting 되었다면, 그 directorID
                "(select MAX(directorID)\n" +
                "from make natural join casting natural join actor_more_than_once \n" +
                "group by actorID\n" +
                "having count(distinct directorID) = 1)\n" +
                "\n" +
                "select directorName\n" + // 그 directorID에 해당하는 directorName
                "from director natural join director_cast");
        pstmt_all_use = connection.prepareStatement("with actor_more_than_once(actorID) as\n" +
                "(select actorID\n" +
                "from casting\n" +
                "group by actorID\n" +
                "having count(*)>1\n" +
                "order by actorID), \n" +
                "\n" +
                "director_cast(directorID) as\n" +
                "(select MAX(directorID)\n" +
                "from make natural join casting natural join actor_more_than_once \n" +
                "group by actorID\n" +
                "having count(distinct directorID) = 1)\n" +
                "\n" +
                "select directorName\n" +
                "from director natural join director_cast");
        rs = pstmt_all_use.executeQuery();

        rsmd = rs.getMetaData();
        System.out.println("\n******************* Result *******************");
        for(int i = 1; i <= rsmd.getColumnCount(); i++) {
            System.out.format("%-26s", "|" + rsmd.getColumnName(i));
        }
        System.out.println();

        while(rs.next()) {
            for(int i = 1; i <= rsmd.getColumnCount(); i++) {
                System.out.format("%-26s", "|" + rs.getObject(i));
            }
            System.out.println();
        }

        // No.6 Statement
        System.out.println("\n\n\n------------------------------------------------- No 6 Statement -------------------------------------------------");
        System.out.println("Statement : Select the names of the movies and the genres, where movies have the common genre");
        System.out.println("Translated SQL : \n" +
                "with cnt_of_genre(genreName, count) as\n" +
                "(select genreName, count(genreName)\n" +
                " from movie natural join movieGenre\n" +
                " group by genreName)\n" +
                "select movieName, genreName\n" +
                "from movieGenre natural join cnt_of_genre natural join movie\n" +
                "where count > 1\n" +
                "order by genreName");
        pstmt_all_use = connection.prepareStatement( "with cnt_of_genre(genreName, count) as\n" +
                "(select genreName, count(genreName)\n" +
                " from movie natural join movieGenre\n" +
                " group by genreName)\n" +
                "select movieName, genreName\n" +
                "from movieGenre natural join cnt_of_genre natural join movie\n" +
                "where count > 1\n" +
                "order by genreName");
        rs = pstmt_all_use.executeQuery();
        rsmd = rs.getMetaData();
        System.out.println("\n******************* Result *******************");
        for(int i = 1; i <= rsmd.getColumnCount(); i++) {
            System.out.format("%-26s", "|" + rsmd.getColumnName(i));
        }
        System.out.println();

        while(rs.next()) {
            for(int i = 1; i <= rsmd.getColumnCount(); i++) {
                System.out.format("%-26s", "|" + rs.getObject(i));
            }
            System.out.println();
        }

        // No.7 Statement
        System.out.println("\n\n\n------------------------------------------------- No 7 Statement -------------------------------------------------");
        System.out.println("Statement : Delete the movies whose director or actor did not get any award and delete data from related tables");
        System.out.println("Translated SQL : \n" +
                "select movieID\n" +
                "from movie as S\n" +
                "where movieID not in (select movieID\n" +
                "from movie natural join make natural join directorObtain\n" +
                ") and movieID not in (select distinct movieID\n" +
                "from movie natural join casting natural join actorObtain)");
        pstmt_all_use = connection.prepareStatement("select movieID\n" +
                "from movie as S\n" +
                "where movieID not in (select movieID\n" +
                "from movie natural join make natural join directorObtain\n" +
                ") and movieID not in (select distinct movieID\n" +
                "from movie natural join casting natural join actorObtain)");
        rs = pstmt_all_use.executeQuery();

        while (rs.next()) {
            movie_id = rs.getInt(1); // movie_id = 3;
            System.out.println("Translated SQL : DELETE FROM movie WHERE movieID = '"+ movie_id +"'");
            pstmt_all_use = connection.prepareStatement("DELETE FROM movie WHERE movieID = '"+ movie_id +"'");
            pstmt_all_use.executeUpdate();
        }

        print_updated_table(connection, "movie");


        // No.8 Statement
        System.out.println("\n\n\n------------------------------------------------- No 8 Statement -------------------------------------------------");
        System.out.println("Statement : Delete all customers and delete data from related tables");
        System.out.println("Translated SQL : delete from customer");
        pstmt_all_use = connection.prepareStatement("delete from customer");
        pstmt_all_use.executeUpdate();

        // customer와 customerRate의 모든 tuple이 삭제 되었으므로 각 movie의 avgRate update
        pstmt_all_use = connection.prepareStatement("select movieID from movie");
        rs = pstmt_all_use.executeQuery();
        while (rs.next()) {
            movie_id = rs.getInt(1); // movie_id = 1, 2, 3, 4, 5
            update_movie_avgRate(connection, movie_id);
        }

        print_updated_table(connection, "customer");
        print_updated_table(connection, "movie");


        // No.9 Statement
        System.out.println("\n\n\n------------------------------------------------- No 9 Statement -------------------------------------------------");
        System.out.println("Statement : Delete all tables and data (make the database empty)");

        // delete all tuples in every table
        delete_table(connection, "make");
        delete_table(connection, "casting");
        delete_table(connection, "directorObtain");
        delete_table(connection, "actorObtain");
        delete_table(connection, "movieObtain");
        delete_table(connection, "movieGenre");
        delete_table(connection, "genre");
        delete_table(connection, "award");
        delete_table(connection, "movie");
        delete_table(connection, "actor");
        delete_table(connection, "director");
        System.out.println();

        // drop every table
        drop_table(connection, "customerRate");
        drop_table(connection, "customer");
        drop_table(connection, "make");
        drop_table(connection, "casting");
        drop_table(connection, "directorObtain");
        drop_table(connection, "actorObtain");
        drop_table(connection, "movieObtain");
        drop_table(connection, "movieGenre");
        drop_table(connection, "genre");
        drop_table(connection, "award");
        drop_table(connection, "movie");
        drop_table(connection, "actor");
        drop_table(connection, "director");

        System.out.println("All tables and data are deleted successfully !! ^^");

        // 비밀번호 변경

        connection.close();
    }
}