#!/bin/sh
select=1
a=7
while [ "$select" -le "$a" ]
do
    echo -e "MENU\n 1) Create address book\n 2) View address book\n 3) Insert a record\n 4) Search a record\n 5) Delete a record\n 6) Modify a record\n 7) Exit\n Enter your choice: "
    read choice
    
    create() {
        touch File3.txt
        echo "RollNo\t Name\t Phone-Number\t Address\n" > File3.txt
    }

    insert() {
        echo -e "RollNo: "
        read roll
        echo -e "Name: "
        read name
        echo -e "Phone: "
        while true
        do
            read phone
            len=$(echo -n $phone | wc -m)
            if [ "$len" -eq 10 ]; then
                break
            else
                echo -e "Please enter a 10-digit number."
            fi
        done
        echo -e "Address: "
        read address
        echo -e "$roll\t$name\t$phone\t\t $address\n" >> File3.txt
    }

    search() {
        echo -n "Enter the phone number to be searched: "
        read phon2
        grep -q "$phon2" File3.txt
        if [ $? -ne 0 ]; then
            echo "Record Not found"
        else
            grep -i -w "$phon2" File3.txt
            echo "Record found"
        fi
    }

    delete() {
        echo -n "Enter the phone number to be deleted: "
        read phon
        grep -q -w "$phon" File3.txt
        if [ $? -ne 0 ]; then
            echo "Record Not found"
        else
            grep -v -i -w "$phon" File3.txt > File2.txt
            mv File2.txt File3.txt
            echo "Record Deleted"
        fi
    }

    modify() {
        echo -n "Enter the phone number to be modified: "
        read phon1
        grep -q -w "$phon1" File3.txt
        if [ $? -ne 0 ]; then
            echo "Record Not found"
        else
            grep -v -i -w "$phon1" File3.txt > q.txt
            mv q.txt File3.txt
            insert
        fi
    }

    case "$choice" in
        1) create ;;      
        2) cat File3.txt ;;
        3)
            x=1
            y=1
            while [ "$x" -eq "$y" ]
            do
                insert
                echo -n "Do you want to add another record? Press 1 to continue, 2 to stop: "
                read x
            done
        ;;
        4) search ;;
        5) delete ;;
        6) modify ;;
        7) exit ;;
        *) echo "Invalid choice!!!" ;;
    esac
done
