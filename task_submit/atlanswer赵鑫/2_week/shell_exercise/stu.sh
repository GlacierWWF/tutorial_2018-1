#! /bin/bash
#Check file status
if test ! -r ./stu.txt
then
    echo "File ./stu.txt not exist or not readable."
    exit 1
fi
stu="./stu.txt"

#Check parameters
if [ ! -n "$1" ]
then
    cat ${stu}
    exit 0
elif [ $# -ne 2 ]
then
    echo "Too many parameters: $#"
    exit 1
fi

#Functions
showHelp() {
    echo "Usage: ./stu.sh [OPTION] [VALUE]"
    echo -e "A shell script to process stu.txt.\n"
    echo -e "Options:\n -a value\t首先判断记录是否存在，如果不存在，则把该信息写入文件，如果存在，则给出提示，并输出文件中学号为value的该行信息"
    echo -e " -d value\t首先判断记录是否存在，如果不存在，给出提示，如果存在，则提示用户确认是否要删除记录，如用户输入y或者yes，则删除文件中学号为value的该行信息，如果用户输入n或no时，则不做删除操作"
    echo -e " -s value\t首先判断记录是否存在，如果不存在，给出提示，如果存在，则输出文件中学号为value的该行信息\n"
    echo "By default, ./stu.sh lists all records."
}

append() {
    #Cut the id
    newid=${1:0:3}
    #Check if the record already exists
    for record in `cat ${stu}`; do
        id=${record:0:3}
        if [ ${newid} = ${id} ]
        then
            echo "The same record id already exists."
            echo "Record in stu.txt: ${record}"
            return 0
        fi
    done
    #Append the record
    echo -e "\n$1\c" >> $stu
}

delete() {
    #Cut the id
    newid=${1:0:3}
    #Check if the record already exists
    for record in `cat ${stu}`; do
        id=${record:0:3}
        if [ ${newid} = ${id} ]
        then
            read -p "Proceed with deletion? [y(yes)/n(no)] " reply
            #Comfirmed
            if [ ${reply} = "y" -o ${reply} = "yes" ]
            then
                sed -i "/${newid}/d" ${stu}
            #Not comfirmed
            elif [ ${reply} = "n" -o ${reply} = "no" ]
            then
                return 0
            #Other
            else
                echo "Not recognized."
            fi
            return 0
        fi
    done
    #Record not exists
    echo "The record with id ${newid} does not exist."
}

search() {
    #Cut the id
    newid=${1:0:3}
    #Check if the record already exists
    for record in `cat ${stu}`; do
        id=${record:0:3}
        if [ ${newid} = ${id} ]
        then
            echo "The record with id ${newid} exists."
            echo "Record in stu.txt: ${record}"
            return 0
        fi
    done
    #Not found
    echo "The record with id ${newid} can not be found."
}

#Read options and parameters
case "$1" in
    -a) append $2 ;;
    -d) delete $2 ;;
    -s) search $2 ;;
    *) echo "Option $1 not recognized."
        showHelp;;
esac