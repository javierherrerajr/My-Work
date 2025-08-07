// app/courses/page.tsx (Server Component)
import { prisma } from "@/lib/prisma";
import { ClientCourseList } from "@/components/ClientCourseList";

export const dynamic = 'force-dynamic'

export default async function CoursesPage() {
  const initialCourses = await prisma.class.findMany({
    orderBy: { courseid: "asc" },
  });

  return <ClientCourseList initialCourses={initialCourses} />;
}
