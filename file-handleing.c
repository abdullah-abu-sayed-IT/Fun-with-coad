#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "todo_list.txt"

// টাস্কের জন্য স্ট্রাকচার
struct Task {
    int id;
    char title[100];
    int is_completed; // ০ মানে বাকি আছে, ১ মানে শেষ
};

// নতুন টাস্ক যোগ করার ফাংশন
void addTask() {
    FILE *file = fopen(FILE_NAME, "ab"); // Append Binary Mode
    if (file == NULL) {
        printf("ফাইল ওপেন করা যাচ্ছে না!\n");
        return;
    }

    struct Task newTask;
    
    // অটো-আইডি জেনারেট করার জন্য ফাইলের সাইজ চেক করা
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    newTask.id = (size / sizeof(struct Task)) + 1;

    printf("\nনতুন টাস্কের নাম লিখুন: ");
    getchar(); // বাফার ক্লিয়ার
    fgets(newTask.title, sizeof(newTask.title), stdin);
    newTask.title[strcspn(newTask.title, "\n")] = 0; // নতুন লাইন রিমুভ
    newTask.is_completed = 0; // শুরুতে টাস্কটি অসম্পূর্ণ থাকবে

    fwrite(&newTask, sizeof(struct Task), 1, file);
    fclose(file);
    printf("✔ টাস্কটি সফলভাবে যোগ করা হয়েছে! (আইডি: %d)\n", newTask.id);
}

// সব টাস্ক দেখার ফাংশন
void viewTasks() {
    FILE *file = fopen(FILE_NAME, "rb"); // Read Binary Mode
    if (file == NULL) {
        printf("\nকোনো টাস্ক পাওয়া যায়নি। প্রথমে কিছু যোগ করুন।\n");
        return;
    }

    struct Task task;
    printf("\n================ সব টাস্কের তালিকা ================\n");
    printf("%-5s %-40s %-10s\n", "আইডি", "টাস্কের নাম", "স্ট্যাটাস");
    printf("--------------------------------------------------\n");

    while (fread(&task, sizeof(struct Task), 1, file)) {
        printf("%-5d %-40s %-10s\n", 
               task.id, 
               task.title, 
               task.is_completed ? "✓ শেষ" : "⏳ বাকি");
    }
    printf("==================================================\n");
    fclose(file);
}

// টাস্ক সম্পূর্ণ (Complete) করার ফাংশন
void markAsComplete() {
    FILE *file = fopen(FILE_NAME, "r+b"); // Read/Write Binary Mode
    if (file == NULL) {
        printf("কোনো টাস্ক লিস্ট পাওয়া যায়নি!\n");
        return;
    }

    int targetId, found = 0;
    printf("\nসম্পূর্ণ করা টাস্কের আইডি দিন: ");
    scanf("%d", &targetId);

    struct Task task;
    while (fread(&task, sizeof(struct Task), 1, file)) {
        if (task.id == targetId) {
            task.is_completed = 1;
            // কার্সারকে আবার এই রেকর্ডের শুরুতে নিয়ে গিয়ে আপডেট করা
            fseek(file, -sizeof(struct Task), SEEK_CUR);
            fwrite(&task, sizeof(struct Task), 1, file);
            found = 1;
            break;
        }
    }

    fclose(file);
    if (found) {
        printf("✔ টাস্কটি 'সম্পূর্ণ' হিসেবে আপডেট করা হয়েছে!\n");
    } else {
        printf("❌ এই আইডির কোনো টাস্ক পাওয়া যায়নি।\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n--- টাস্ক ম্যানেজার প্রজেক্ট ---\n");
        printf("১. নতুন টাস্ক যোগ করুন\n");
        printf("২. সব টাস্ক দেখুন\n");
        printf("৩. টাস্ক সম্পূর্ণ হিসেবে মার্ক করুন\n");
        printf("৪. এক্সিট (Exit)\n");
        printf("আপনার চয়েস দিন (১-৪): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markAsComplete(); break;
            case 4: 
                printf("প্রোগ্রামটি ব্যবহার করার জন্য ধন্যবাদ!\n");
                exit(0);
            default: 
                printf("ভুল ইনপুট! আবার চেষ্টা করুন।\n");
        }
    }
    return 0;
}
